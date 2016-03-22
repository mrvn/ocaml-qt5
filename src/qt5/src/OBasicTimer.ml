open External

class oBasicTimer obj = object(self)
  inherit OClass.oClass obj
  method as_oBasicTimer = (self :> oBasicTimer)
  method start : 'a . int -> (<as_oObject : OObject.oObject; ..> as 'a) -> unit = fun msec obj ->
    let module E = (val (module struct
      type e = oBasicTimer OClass.t -> int -> OObject.t -> unit
      external stub : oBasicTimer OClass.t -> int  -> OObject.t -> unit= "caml_mrvn_QT5_OBasicTimer_start"
    end) : External with type e = oBasicTimer OClass.t -> int -> OObject.t -> unit)
    in
    E.stub self#as_oBasicTimer#obj msec obj#as_oObject#obj
  method stop =
    let module E = (val (module struct
      type e = oBasicTimer OClass.t -> unit
      external stub : oBasicTimer OClass.t -> unit = "caml_mrvn_QT5_OBasicTimer_stop"
    end) : External with type e = oBasicTimer OClass.t -> unit)
    in
    E.stub self#as_oBasicTimer#obj
  method timerId =
    let module E = (val (module struct
      type e = oBasicTimer OClass.t -> int
      external stub : oBasicTimer OClass.t -> int = "caml_mrvn_QT5_OBasicTimer_timerId"
    end) : External with type e = oBasicTimer OClass.t -> int)
    in
    E.stub self#as_oBasicTimer#obj
end

type t = oBasicTimer OClass.t

module type Make = sig
  val stub : unit -> #oBasicTimer OClass.t
end

class qBasicTimer () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oBasicTimer OClass.t = "caml_mrvn_QT5_OBasicTimer_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oBasicTimer obj
end
