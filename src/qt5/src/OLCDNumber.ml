open External

type mode =
| Hex
| Dec
| Oct
| Bin
  
type segmentStyle =
| Outline
| Filled
| Flat

class oLCDNumber obj = object(self)
  inherit OFrame.oFrame obj
  method as_oLCDNumber = (self :> oLCDNumber)
  method setMode mode =
    let module E = (val (module struct
      type e = oLCDNumber OClass.t -> int -> unit
      external stub : oLCDNumber OClass.t -> int -> unit = "caml_mrvn_QT5_OLCDNumber_setMode"
    end) : External with type e = oLCDNumber OClass.t -> int -> unit)
    in
    let t =
      match mode with
      | Hex -> 0
      | Dec -> 1
      | Oct -> 2
      | Bin -> 3
    in
    E.stub self#as_oLCDNumber#obj t
  method setSegmentStyle style =
    let module E = (val (module struct
      type e = oLCDNumber OClass.t -> int -> unit
      external stub : oLCDNumber OClass.t -> int -> unit = "caml_mrvn_QT5_OLCDNumber_setSegmentStyle"
    end) : External with type e = oLCDNumber OClass.t -> int -> unit)
    in
    let t =
      match style with
      | Outline -> 0
      | Filled  -> 1
      | Flat    -> 2
    in
    E.stub self#as_oLCDNumber#obj t
  method display num =
    let module E = (val (module struct
      type e = oLCDNumber OClass.t -> int -> unit
      external stub : oLCDNumber OClass.t -> int -> unit = "caml_mrvn_QT5_OLCDNumber_display"
    end) : External with type e = oLCDNumber OClass.t -> int -> unit)
    in
    E.stub self#as_oLCDNumber#obj num
end

type t = oLCDNumber OClass.t

module type Make = sig
  val stub : int -> #oLCDNumber OClass.t
end

class qLCDNumber numDigits =
  let obj =
    let module E = (val (module struct
      external stub : int -> #oLCDNumber OClass.t = "caml_mrvn_QT5_OLCDNumber_make"
    end) : Make)
    in
    E.stub numDigits
  in
object
  inherit oLCDNumber obj
end
