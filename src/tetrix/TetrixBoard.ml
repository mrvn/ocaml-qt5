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
  
class tetrixBoard nextPieceLabel =
  let boardWidth = 10 in
  let boardHeight = 22
  in
object(self)
  inherit OFrame.qFrame ()
  val scoreChanged = new signal
  val levelChanged = new signal
  val linesRemovedChanged = new signal
  val mutable isStarted = false
  val mutable isPaused = false
    (*
    QBasicTimer timer;
    *)
  val mutable isWaitingAfterLine = false
  val curPiece = TetrixPiece.noShape
  val nextPiece = TetrixPiece.randomShape ()
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
(*
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
*)
  method scoreChanged = (scoreChanged : int signal)
  method levelChanged = (levelChanged : int signal)
  method linesRemovedChanged = (linesRemovedChanged : int signal)
(*
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
private:
*)
  method private shapeAt x y = board.((y * boardWidth) + x)
  method private timeoutTime = 1000 / (1 + level)
  (*
  method private squareWidth = self#contentsRect#width / boardWidth
  method private squareHeight = self#contentsRect#height / boardHeight
  *)
  method private clearBoard =
    for i = 0 to boardHeight * boardWidth - 1 do
      board.(i) <- TetrixPiece.(noShape.color);
    done

  method sizeHint = (boardWidth * 15 + self#frameWidth * 2,
                     boardHeight * 15 + self#frameWidth * 2)
  method minimumSizeHint = (boardWidth * 5 + self#frameWidth * 2,
                            boardHeight * 5 + self#frameWidth * 2)

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
      (*
      timer.start(timeoutTime(), this);
      *)
    end

  method pause =
    if isStarted
    then begin
      isPaused <- not isPaused;
      if isPaused
      then () (* timer#stop *)
      else (); (* timer#start(timeoutTime(), this); *)
      self#update;
    end

  inherit OWidget.paintEvent
  method paintEvent event =
    Printf.printf "tetrixBoard.paintEvent\n";
    self#qPaintEvent event;
    (*
    let painter = new OPainter.oPainter self#as_oPaintDevice in
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
            let (x, y) = (curX + x, curY + y)
            in 
            self#drawSquare
              painter
              (rect#left + x * self#squareWidth)
              (boardTop + (boardHeight - y - 1) * self#squareHeight)
              curPiece.color
          done)
    *)

  method newPiece = ()
  method update = ()
(*
void TetrixBoard::keyPressEvent(QKeyEvent *event)
{
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

void TetrixBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void TetrixBoard::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
}

void TetrixBoard::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped(0);
}

void TetrixBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        shapeAt(x, y) = curPiece.shape();
    }

    ++numPiecesDropped;
    if (numPiecesDropped % 25 == 0) {
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight + 7;
    emit scoreChanged(score);
    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
}

void TetrixBoard::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }
            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, BoardHeight - 1) = NoShape;
        }
    }

    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        update();
    }
}

void TetrixBoard::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + curPiece.minY();

    if (!tryMove(curPiece, curX, curY)) {
        curPiece.setShape(NoShape);
        timer.stop();
        isStarted = false;
    }
}

void TetrixBoard::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(),
                   nextPiece.shape());
    }
    nextPieceLabel->setPixmap(pixmap);
}

bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}

void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}

*)
end
