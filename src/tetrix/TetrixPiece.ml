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

type tetrixShape =
| NoShape
| ZShape
| SShape
| LineShape
| TShape
| SquareShape
| LShape
| MirroredLShape

type tetrixPiece = {
  color : QT5.OColor.qColor;
  coords : (int * int) array;
}

let noShape = {
  color = new QT5.OColor.qColor("#000000");
  coords = [| (0, 0); (0, 0); (0, 0); (0, 0); |];
}

let zShape = {
  color = new QT5.OColor.qColor("#CC6666");
  coords = [| ( 0, -1); ( 0,  0); (-1,  0); (-1,  1); |];
}

let sShape = {
  color = new QT5.OColor.qColor("#66CC66");
  coords = [| ( 0, -1); ( 0,  0); ( 1,  0); ( 1,  1); |];
}

let lineShape = {
  color = new QT5.OColor.qColor("#6666CC");
  coords = [| ( 0, -1); ( 0,  0); ( 0,  1); ( 0,  2); |];
}

let tShape = {
  color = new QT5.OColor.qColor("#CCCC66");
  coords = [| (-1,  0); ( 0,  0); ( 1,  0); ( 0,  1); |];
}

let squareShape = {
  color = new QT5.OColor.qColor("#CC66CC");
  coords = [| ( 0,  0); ( 1,  0); ( 0,  1); ( 1,  1); |];
}

let lShape = {
  color = new QT5.OColor.qColor("#66CCCC");
  coords = [| (-1, -1); ( 0, -1); ( 0,  0); ( 0,  1); |];
}

let mirroredLShape = {
  color = new QT5.OColor.qColor("#DAAA00");
  coords = [| ( 1, -1); ( 0, -1); ( 0,  0); ( 0,  1); |];
}

let shapes =
  [|
    noShape;
    zShape;
    sShape;
    lineShape;
    tShape;
    squareShape;
    lShape;
    mirroredLShape;
  |]

let randomShape () =
  shapes.(Random.int 7)

let xy t index = t.coords.(index)

let minXY t =
  Array.fold_left
    (fun (x, y) (u, v) -> (min x u, min y v))
    (0, 0)
    t.coords

let maxXY t =
  Array.fold_left
    (fun (x, y) (u, v) -> (max x u, max y v))
    (0, 0)
    t.coords

let rotatedLeft t =
  {
    t with
      coords = Array.map (fun (x, y) -> (y, -x)) t.coords;
  }
  
let rotatedRight t =
  {
    t with
      coords = Array.map (fun (x, y) -> (-y, x)) t.coords;
  }
