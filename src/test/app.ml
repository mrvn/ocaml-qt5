let res =
  Printf.printf "OApplication test\n%!";
  let a = QT5.OApplication.make Sys.argv in
  let win = QT5.OMainWindow.make () in
  let b = QT5.OPushButton.make "push" in
  let connection =
    b#connect
      (QT5.OAbstractButton.clicked ())
      (fun checked -> Printf.printf "button clicked (ocaml)\n%!")
  in
  QT5.OMainWindow.setCentralWidget win b;
  QT5.OMainWindow.show win;
  let res = a#exec
  in
  b#disconnect connection;
  res

let () = exit res
