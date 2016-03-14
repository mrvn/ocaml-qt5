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

let foo _ = Printf.printf "start callback\n%!"

class tetrixWindow () =
  let createLabel text =
    let label = new OLabel.qLabel ~text ()
    in
    label#setAlignment (QT5.Qt.AlignHCenter, Qt.AlignBottom);
    label
  in
object(self)
  inherit OWidget.qWidget ()
  val board = new TetrixBoard.tetrixBoard
  val nextPieceLabel = new OLabel.qLabel ()
  val scoreLcd = new OLCDNumber.qLCDNumber 5
  val levelLcd = new OLCDNumber.qLCDNumber 2
  val linesLcd = new OLCDNumber.qLCDNumber 5
  val startButton = new OPushButton.qPushButton "&Start"
  val quitButton = new OPushButton.qPushButton "&Quit"
  val pauseButton = new OPushButton.qPushButton "&Pause"
  initializer
    nextPieceLabel#setFrameStyle ~shadow:OFrame.Raised ~shape:OFrame.Box ();
    nextPieceLabel#setAlignment Qt.alignCenter;
    board#setNextPieceLabel nextPieceLabel;
    scoreLcd#setSegmentStyle OLCDNumber.Filled;
    levelLcd#setSegmentStyle OLCDNumber.Filled;
    linesLcd#setSegmentStyle OLCDNumber.Filled;
    startButton#setFocusPolicy Qt.NoFocus;
    quitButton#setFocusPolicy  Qt.NoFocus;
    pauseButton#setFocusPolicy Qt.NoFocus;
    let _ = startButton#clicked#connect (fun _ -> Printf.printf "start callback\n%!"; board#start) in
    let _ = pauseButton#clicked#connect (fun _ -> Printf.printf "pause callback\n%!"; board#pause)
    in
    board#scoreChanged#connect scoreLcd#display;
    board#levelChanged#connect levelLcd#display;
    board#linesRemovedChanged#connect linesLcd#display;
    let layout = new OGridLayout.qGridLayout ()
    in
    layout#addWidgetAt (createLabel "NEXT") 0 0;
    layout#addWidgetAt nextPieceLabel 1 0;
    layout#addWidgetAt (createLabel "LEVEL") 2 0;
    layout#addWidgetAt levelLcd 3 0;
    layout#addWidgetAt startButton 4 0;
    layout#addWidgetAt board ~rowSpan:6 0 1;
    layout#addWidgetAt (createLabel "SCORE") 0 2;
    layout#addWidgetAt scoreLcd 1 2;
    layout#addWidgetAt (createLabel "LINES REMOVED") 2 2;
    layout#addWidgetAt linesLcd 3 2;
    layout#addWidgetAt quitButton 4 2;
    layout#addWidgetAt pauseButton 5 2;
    self#setLayout layout;
    self#setWindowTitle "Tetrix";
    self#resize (550, 370)
  method quitClicked = quitButton#clicked
end
