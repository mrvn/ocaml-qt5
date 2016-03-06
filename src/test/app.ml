let handle_event proxy =
  Printf.printf "App.handle_event()\n%!";
  let event = new QT5.OEvent.oEvent proxy
  in
  false
    
let res =
  Printf.printf "OApplication test\n%!";
  let a = QT5.OApplication.make Sys.argv in
  let win = QT5.OMainWindow.make () in
  let b = QT5.OPushButton.make "push" in
  let connection =
    b#clicked#connect
      (fun checked -> Printf.printf "App: button clicked (ocaml)\n%!")
  in
  let () =
    b#handler_event#set
      (fun event -> Printf.printf "App: event received (ocaml)\n%!"; false)
  in
  win#setCentralWidget b;
  win#show;
  let res = a#exec
  in
  b#disconnect connection;
  res

let () = exit res
