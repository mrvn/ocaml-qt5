let res =
  Printf.printf "QApplication test\n%!";
  let a = new QT5.QApplication.qApplication () in
  let w = new QT5.QMainWindow.qMainWindow in
  w#show;
  a#exec
let () = exit res
