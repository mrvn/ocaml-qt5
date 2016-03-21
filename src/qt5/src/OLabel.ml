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
    let align = Qt.int_of_align absolute horizontal vertical
    in
    E.stub self#as_oLabel#obj align
  method setPixmap : 'a . (<as_oPixmap : OPixmap.oPixmap; ..> as 'a) -> unit = fun pixmap ->
(*
  method setPixmap : OPixmap.oPixmap -> unit = fun pixmap ->
*)
    let module E = (val (module struct
      type e = oLabel OClass.t -> OPixmap.t -> unit
      external stub : oLabel OClass.t -> OPixmap.t -> unit = "caml_mrvn_QT5_OLabel_setPixmap"
    end) : External with type e = oLabel OClass.t -> OPixmap.t -> unit)
    in
    E.stub self#as_oLabel#obj pixmap#as_oPixmap#obj
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
