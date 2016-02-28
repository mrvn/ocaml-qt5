type qtCon

type 'a t = {
  qtCon : qtCon;
  fn : 'a;
}

external disconnect : 'a t -> unit
  = "caml_mrvn_QT5_Connection_disconnect"
