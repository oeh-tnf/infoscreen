{ stdenv, qtbase, qtdeclarative, cmake, wrapQtAppsHook, qttools, redhat-official-fonts }:

stdenv.mkDerivation {
  pname = "tnf-infoscreen";
  version = "1.0";

  src = ./.;

  buildInputs = [
    qtbase
    qtdeclarative
    redhat-official-fonts
  ];
  nativeBuildInputs = [
    cmake
    wrapQtAppsHook
  ];
}
