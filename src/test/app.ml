(*
let handle_event proxy =
  Printf.printf "App.handle_event()\n%!";
  let event = new QT5.OEvent.oEvent proxy
  in
  false
*)

class button text = object
  inherit QT5.OPushButton.oPushButton (Obj.magic (QT5.OPushButton.external_make text))
  inherit QT5.OObject.event
  method event event =
    Printf.printf "App: event (ocaml)\n%!";
    false
end

let res =
  Printf.printf "OApplication test\n%!";
  let app = QT5.OApplication.make Sys.argv in
  let b = new button "push" in
  let win = QT5.OMainWindow.make () in
  let connection =
    b#clicked#connect
      (fun checked -> Printf.printf "App: button clicked (ocaml)\n%!")
  in
  win#setCentralWidget b;
  win#show;
  let res = app#exec
  in
  b#disconnect connection;
  res

let () = exit res
