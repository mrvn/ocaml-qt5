(* simple test of a main window with a push button *)
(* - shows how to connect to the clicked signal for the button *)
(* - shows how to catch events processed by the button *)

(* qPushButton with override for:
     event : QEvent -> bool
*)
class button text = object
  inherit QT5.OPushButton.qPushButton text
  inherit QT5.OObject.event
  method event event =
    Printf.printf "App: event (ocaml)\n%!";
    Gc.full_major ();
    Printf.printf "App: event (ocaml) done Gc\n%!";
    false
end

let () = Printf.printf "OApplication test\n%!"
let app = new QT5.OApplication.qApplication Sys.argv
let win = new QT5.OMainWindow.qMainWindow ()

let res =
  let b = new button "push" in
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
