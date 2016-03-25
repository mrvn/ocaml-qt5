(****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************)
(* Modified for ocaml by Goswin von Brederlow                              *)

open QT5

class ['a] signal = object
  val mutable callbacks = ([] : ('a -> unit) list)
  method connect callback = callbacks <- callback :: callbacks
  method emit x = List.iter (fun callback -> callback x) callbacks
end
  
class tetrixBoard (nextPieceLabel : #OLabel.oLabel) =
  let boardWidth = 10 in
  let boardHeight = 22
  in
object(self)
  inherit OFrame.qFrame ()
  inherit OWidget.sizeHint
  inherit OWidget.minimumSizeHint
  inherit OWidget.keyPressEvent
  inherit OWidget.paintEvent
  inherit OObject.timerEvent
    
  val scoreChanged = new signal
  val levelChanged = new signal
  val linesRemovedChanged = new signal
  val mutable isStarted = false
  val mutable isPaused = false
  val timer = new OBasicTimer.qBasicTimer ()
  val mutable isWaitingAfterLine = false
  val mutable curPiece = TetrixPiece.noShape
  val mutable nextPiece = TetrixPiece.randomShape ()
  val mutable curX = 0
  val mutable curY = 0
  val mutable numLinesRemoved = 0
  val mutable numPiecesDropped = 0
  val mutable score = 0
  val mutable level = 0
  val board = Array.init (boardWidth * boardHeight) (fun _ -> TetrixPiece.(noShape.color))

  initializer
    self#setFrameStyle ~shadow:OFrame.Sunken ~shape:OFrame.Panel ();
    self#setFocusPolicy Qt.StrongFocus;

  method scoreChanged = (scoreChanged : int signal)

  method levelChanged = (levelChanged : int signal)

  method linesRemovedChanged = (linesRemovedChanged : int signal)

  method private shapeAt x y = board.((y * boardWidth) + x)

  method private setShapeAt x y c = board.((y * boardWidth) + x) <- c

  method private timeoutTime = 1000 / (1 + level)

  method private squareWidth = self#contentsRect#width / boardWidth

  method private squareHeight = self#contentsRect#height / boardHeight

  method private clearBoard =
    for i = 0 to boardHeight * boardWidth - 1 do
      board.(i) <- TetrixPiece.(noShape.color);
    done

  method sizeHint =
    new OSize.qSize
      (boardWidth * 15 + self#frameWidth * 2)
      (boardHeight * 15 + self#frameWidth * 2)

  method minimumSizeHint =
    new OSize.qSize
      (boardWidth * 5 + self#frameWidth * 2)
      (boardHeight * 5 + self#frameWidth * 2)

  method start =
    if isPaused
    then ()
    else begin
      isStarted <- true;
      isWaitingAfterLine <- false;
      numLinesRemoved <- 0;
      numPiecesDropped <- 0;
      score <- 0;
      level <- 1;
      self#clearBoard;

      linesRemovedChanged#emit numLinesRemoved;
      scoreChanged#emit score;
      levelChanged#emit level;

      self#newPiece;
      timer#start self#timeoutTime self;
    end

  method pause =
    if isStarted
    then begin
      isPaused <- not isPaused;
      if isPaused
      then timer#stop
      else timer#start self#timeoutTime self;
      self#update;
    end

  method paintEvent event =
    Printf.printf "tetrixBoard.paintEvent\n";
    self#qPaintEvent event;
    (* Gc.full_major (); *)
    Printf.printf "### painter\n%!";
    let painter = new OPainter.qPainter () in
    assert (painter#begin_ self);
    begin
      let rect = self#contentsRect
      in
      if isPaused
      then painter#drawText rect Qt.alignCenter "Pause"
      else
        let boardTop = rect#bottom - boardHeight * self#squareHeight
        in
        TetrixPiece.(
          for i = 0 to boardHeight - 1 do
            for j = 0 to boardWidth - 1 do
              let color = self#shapeAt j (boardHeight - i - 1)
              in
              if color != noShape.color
              then
                self#drawSquare
                  painter
                  (rect#left + j * self#squareWidth)
                  (boardTop + i * self#squareHeight)
                  color;
            done
          done;
          if curPiece.color != noShape.color
          then
            for i = 0 to 3 do
              let (x, y) = xy curPiece i in
              let (x, y) = (curX + x, curY - y)
              in
              self#drawSquare
                painter
                (rect#left + x * self#squareWidth)
                (boardTop + (boardHeight - y - 1) * self#squareHeight)
                curPiece.color
            done);
    end;
    painter#end_

  method keyPressEvent event =
    self#qKeyPressEvent event
(*
    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(curPiece, curX - 1, curY);
        break;
    case Qt::Key_Right:
        tryMove(curPiece, curX + 1, curY);
        break;
    case Qt::Key_Down:
        tryMove(curPiece.rotatedRight(), curX, curY);
        break;
    case Qt::Key_Up:
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;
    case Qt::Key_Space:
        dropDown();
        break;
    case Qt::Key_D:
        oneLineDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}
*)
  method timerEvent event =
    Printf.printf "TetrixBoard#timerEvent\n%!";
    if event#timerId == timer#timerId
    then
      begin
        Printf.printf "TetrixBoard#timerEvent: ==\n%!";
        if isWaitingAfterLine
        then
          begin
            Printf.printf "TetrixBoard#timerEvent: isWaitingAfterLine\n%!";
            isWaitingAfterLine <- false;
            self#newPiece;
            timer#start self#timeoutTime self;
          end
        else
          begin
            Printf.printf "TetrixBoard#timerEvent: oneLineDown\n%!";
          self#oneLineDown
          end
      end
    else
      begin
        Printf.printf "TetrixBoard#timerEvent: not my event\n%!";
        self#qTimerEvent event;
      end;
    Printf.printf "TetrixBoard#timerEvent done\n%!";

  method dropDown =
    let rec loop dropHeight = function
      | 0 -> dropHeight
      | newY ->
        if self#tryMove curPiece curX (newY - 1)
        then loop (dropHeight + 1) (newY - 1)
        else dropHeight
    in
    let dropHeight = loop 0 curY
    in
    self#pieceDropped dropHeight

  method oneLineDown =
    Printf.printf "TetrixBoard#oneLineDown\n%!";
    if not (self#tryMove curPiece curX (curY - 1))
    then self#pieceDropped 0

  method pieceDropped dropHeight =
    Printf.printf "TetrixBoard#pieceDropped %d\n%!" dropHeight;
    for i = 0 to 3 do
      let (x, y) = TetrixPiece.xy curPiece i in
      let (x, y) = (curX + x, curY - y)
      in
      self#setShapeAt x y curPiece.TetrixPiece.color
    done;

    numPiecesDropped <- numPiecesDropped + 1;
    if numPiecesDropped mod 25 == 0
    then begin
      level <- level + 1;
      timer#start self#timeoutTime self;
      levelChanged#emit level;
    end;

    score <- score + dropHeight + 7;
    scoreChanged#emit score;
    self#removeFullLines;

    if not isWaitingAfterLine
    then self#newPiece;
    Printf.printf "TetrixBoard#pieceDropped done\n%!"

  method removeFullLines =
    let numFullLines = ref 0
    in
    for i = boardHeight - 1 downto 0 do
      let rec loop = function
        | j when j == boardWidth -> true
        | j ->
          if self#shapeAt j i == TetrixPiece.(noShape.color)
          then false
          else loop (j + 1)
      in
      let lineIsFull = loop 0
      in
      if lineIsFull
      then begin
        numFullLines := !numFullLines + 1;
        for k = i to boardHeight - 2 do
          for j = 0 to boardWidth - 1 do
            self#setShapeAt j k (self#shapeAt j (k + 1));
          done;
        done;
        for j = 0 to boardWidth - 1 do
          self#setShapeAt j (boardHeight - 1) TetrixPiece.(noShape.color);
        done;
      end;
    done;

    if !numFullLines > 0
    then begin
      numLinesRemoved <- numLinesRemoved + !numFullLines;
      score <- score + 10 * !numFullLines;
      linesRemovedChanged#emit numLinesRemoved;
      scoreChanged#emit score;

      timer#start 500 self;
      isWaitingAfterLine <- true;
      curPiece <- TetrixPiece.noShape;
      self#update;
    end

  method newPiece =
    curPiece <- nextPiece;
    nextPiece <- TetrixPiece.randomShape ();
    self#showNextPiece;
    let (_, minY) = TetrixPiece.minXY curPiece
    in
    curX <- boardWidth / 2 + 1;
    curY <- boardHeight - 1 + minY;
    Printf.printf "### newPiece: curY %d = %d - 1 + %d\n%!"
      curY boardHeight minY;
      
    if not (self#tryMove curPiece curX curY)
    then begin
      curPiece <- TetrixPiece.noShape;
      timer#stop;
      isStarted <- false;
      Printf.printf "### Game Over ###\n%!";
    end

  method showNextPiece =
    let (maxX, maxY) = TetrixPiece.maxXY nextPiece in
    let (minX, minY) = TetrixPiece.minXY nextPiece in
    let (dx, dy) = (maxX - minX + 1, maxY - minY + 1) in
    let pixmap =
      new QT5.OPixmap.qPixmap (dx * self#squareWidth) (dy * self#squareHeight)
    in
    Gc.full_major ();
    Printf.printf "### painter\n%!";
    let painter = new QT5.OPainter.qPainter () in
    assert (painter#begin_ pixmap);
    begin
      painter#fillRect pixmap#rect nextPieceLabel#palette#background;

      let (mx, my) = TetrixPiece.minXY nextPiece in
      for i = 0 to 3 do
        let (x, y) = TetrixPiece.xy nextPiece i in
        let (x, y) = (x - mx, y - my)
        in
        Printf.printf "### drawSquare %d %d\n%!" x y;
        self#drawSquare
          painter
          (x * self#squareWidth)
          (y * self#squareHeight)
          nextPiece.TetrixPiece.color;
      done;
    end;
    painter#end_;
    nextPieceLabel#setPixmap pixmap

  method tryMove newPiece newX newY =
    let rec loop = function
      | 4 ->
        curPiece <- newPiece;
        curX <- newX;
        curY <- newY;
        self#update;
        true
      | i -> 
        let (x, y) = TetrixPiece.xy newPiece i in
        let (x, y) = (newX + x, newY - y)
        in
        if (x < 0) || (x >= boardWidth) || (y < 0) || (y >= boardHeight)
        then false
        else
          if self#shapeAt x y != TetrixPiece.(noShape.color)
          then false
          else loop (i + 1)
    in
    loop 0

  method drawSquare painter x y color =
    Printf.printf "### drawSquare %d %d\n%!" x y;
    painter#fillRectXYWH
      (x + 1)
      (y + 1)
      (self#squareWidth - 2)
      (self#squareHeight - 2)
      color;

    painter#setPenColor color#lighter;
    painter#drawLine x (y + self#squareHeight - 1) x y;
    painter#drawLine x y (x + self#squareWidth - 1) y;

    painter#setPenColor color#darker;
    painter#drawLine
      (x + 1) (y + self#squareHeight - 1)
      (x + self#squareWidth - 1) (y + self#squareHeight - 1);
    painter#drawLine
      (x + self#squareWidth - 1) (y + self#squareHeight - 1)
      (x + self#squareWidth - 1) (y + 1)
end
