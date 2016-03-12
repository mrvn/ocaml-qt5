type ('a, 'b) t

external connect :
  'a OClass.t -> ('a, 'b) t -> 'b -> Connection.t
    = "caml_mrvn_QT5_Signal_connect"

class ['a, 'b] signal (obj : 'a) signal =
object
  method connect (fn : 'b) = connect obj#obj signal fn
end
