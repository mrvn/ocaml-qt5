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

class tetrixPiece = object(self)
  val mutable pieceShape = NoShape
  val coords = [| [| 0;  0|]; [| 0;  0|]; [| 0;  0|]; [| 0;  0|]; |]
  initializer self#setShape NoShape
  method as_self = (self :> tetrixPiece)
  method setRandomShape =
    self#setShape
      (match Random.int 7 with
      | 0 -> ZShape
      | 1 -> SShape
      | 2 -> LineShape
      | 3 -> TShape
      | 4 -> SquareShape
      | 5 -> LShape
      | _ -> MirroredLShape)
  method setShape shape =
    Array.iteri
      (fun i t -> coords.(i) <- Array.copy t)
      (match shape with
      | NoShape        -> [| [| 0;  0|]; [| 0;  0|]; [| 0;  0|]; [| 0;  0|]; |]
      | ZShape         -> [| [| 0; -1|]; [| 0;  0|]; [|-1;  0|]; [|-1;  1|]; |]
      | SShape         -> [| [| 0; -1|]; [| 0;  0|]; [| 1;  0|]; [| 1;  1|]; |]
      | LineShape      -> [| [| 0; -1|]; [| 0;  0|]; [| 0;  1|]; [| 0;  2|]; |]
      | TShape         -> [| [|-1;  0|]; [| 0;  0|]; [| 1;  0|]; [| 0;  1|]; |]
      | SquareShape    -> [| [| 0;  0|]; [| 1;  0|]; [| 0;  1|]; [| 1;  1|]; |]
      | LShape         -> [| [|-1; -1|]; [| 0; -1|]; [| 0;  0|]; [| 0;  1|]; |]
      | MirroredLShape -> [| [| 1; -1|]; [| 0; -1|]; [| 0;  0|]; [| 0;  1|]; |]);
    pieceShape <- shape
  method shape = pieceShape
  method x index = coords.(index).(0)
  method y index = coords.(index).(1)
  method minX =
    Array.fold_left
      (fun res t -> min res t.(0))
      coords.(0).(0)
      coords
  method maxX =
    Array.fold_left
      (fun res t -> max res t.(0))
      coords.(0).(0)
      coords
  method minY =
    Array.fold_left
      (fun res t -> min res t.(1))
      coords.(0).(1)
      coords
  method maxY =
    Array.fold_left
      (fun res t -> max res t.(1))
      coords.(0).(1)
      coords
  method rotatedLeft =
    if pieceShape = SquareShape
    then self#as_self
    else
      let result = new tetrixPiece
      in
      result#setShape pieceShape;
      for i = 0 to 3 do
        result#setX i (self#y i);
        result#setY i (-self#x i);
      done;
      result
  method rotatedRight =
    if pieceShape = SquareShape
    then self#as_self
    else
      let result = new tetrixPiece
      in
      result#setShape pieceShape;
      for i = 0 to 3 do
        result#setX i (-self#y i);
        result#setY i (self#x i);
      done;
      result
  method setX index x = coords.(index).(0) <- x
  method setY index y = coords.(index).(1) <- y
end
