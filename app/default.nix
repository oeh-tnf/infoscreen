{ stdenv, qtbase, qtdeclarative, cmake, wrapQtAppsHook, qttools }:

stdenv.mkDerivation {
  pname = "tnf-infoscreen";
  version = "1.0";

  src = ./.;

  buildInputs = [
    qtbase
    qtdeclarative
  ];
  nativeBuildInputs = [
    cmake
    wrapQtAppsHook
  ];
}
