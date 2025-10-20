cmake_minimum_required(VERSION 3.19)

project(tnf-infoscreen VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 COMPONENTS Quick REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(tnf-infoscreen
    tnf-infoscreen.cpp
    CurrentTime.cpp
    DepartureModel.cpp
    DeparturesSortFilterProxyModel.cpp
    LinzagDepartureModel.cpp
    LinzagDepartureSource.cpp
    MensaMenuModel.cpp
    MensaMenuSource.cpp
    OoevvDepartureModel.cpp
    OoevvDepartureSource.cpp
)

qt_add_qml_module(tnf-infoscreen
    URI TnfInfoscreen
    QML_FILES
        TnfInfoscreen.qml
)

install(TARGETS tnf-infoscreen
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(tnf-infoscreen PRIVATE Qt6::Qml Qt6::Quick)
