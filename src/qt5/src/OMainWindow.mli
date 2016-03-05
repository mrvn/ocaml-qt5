class ['a] oMainWindow :
  'a Proxy.t ->
  object
    constraint 'a = 'a oMainWindow
    val proxy : 'a Proxy.t
    method centralWidget : 'c OWidget.oWidget OWidget.oWidget
    method connect : ('a, 'b) Signal.t -> 'b -> Connection.t
    method disconnect : Connection.t -> unit
    method proxy : 'a Proxy.t
    method setCentralWidget : 'd OWidget.oWidget OWidget.oWidget -> unit
    method show : unit
  end
type t = ('a oMainWindow as 'a) oMainWindow
val make : unit -> ('a oMainWindow as 'a) oMainWindow
