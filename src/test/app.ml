let () = Printf.printf "QApplication test\n%!"
let a = new QT5.QApplication.qApplication
let w = new QT5.QMainWindow.qMainWindow
let () = w#show
let () = exit a#exec
