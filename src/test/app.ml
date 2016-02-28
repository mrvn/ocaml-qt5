let res =
  Printf.printf "QApplication test\n%!";
  let a = new QT5.QApplication.qApplication Sys.argv in
  let win = new QT5.QMainWindow.qMainWindow in
  let b = QT5.QPushButton.make "push" in
  let connection =
    b#connect
      b#clicked
      (fun checked -> Printf.printf "button clicked (ocaml)\n%!")
  in
  win#setCentralWidget b;
  win#show;
  let res = a#exec
  in
  b#disconnect connection;
  res

let () = exit res
