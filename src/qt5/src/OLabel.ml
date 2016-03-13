open External

class oLabel obj = object(self)
  inherit OFrame.oFrame obj
  method as_oLabel = (self :> oLabel)
  method setAlignment ?(absolute=false) (horizontal, vertical) =
    let module E = (val (module struct
      type e = oLabel OClass.t -> int -> unit
      external stub : oLabel OClass.t -> int -> unit = "caml_mrvn_QT5_OLabel_setAlignment"
    end) : External with type e = oLabel OClass.t -> int -> unit)
    in
    let align =
      if absolute
      then 0x10
      else 0
    in
    let align = align lor
      match horizontal with
      | Qt.AlignLeft    -> 0x0001
      | Qt.AlignRight   -> 0x0002
      | Qt.AlignHCenter -> 0x0004
      | Qt.AlignJustify -> 0x0008
    in
    let align = align lor
      match vertical with
      | Qt.AlignTop      -> 0x0020
      | Qt.AlignBottom   -> 0x0040
      | Qt.AlignVCenter  -> 0x0080
      | Qt.AlignBaseline -> 0x0100
    in
    E.stub self#as_oLabel#obj align
end

type t = oLabel OClass.t

module type Make = sig
  val stub : string -> #oLabel OClass.t
end

class qLabel ?(text="") () =
  let obj =
    let module E = (val (module struct
      external stub : string -> #oLabel OClass.t = "caml_mrvn_QT5_OLabel_make"
    end) : Make)
    in
    E.stub text
  in
object
  inherit oLabel obj
end
