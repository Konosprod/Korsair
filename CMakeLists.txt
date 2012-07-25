# set project's name
  PROJECT( korsair )
  
  cmake_minimum_required(VERSION 2.8)
  
  # with SET() command you can change variables or define new ones
  # here we define KORSAIR_SRCS variable that contains a list of all .cpp files
  # note that we don't need \ at the end of line
  SET( KORSAIR_SRCS
    main.cpp
    mainwindow.cpp
    preferencewindow.cpp
  )
  
  # another list, this time it includes all header files that should be treated with moc
  SET( KORSAIR_MOC_HDRS
    mainwindow.h
    preferencewindow.h
  )
  
  SET( KORSAIR_UIS
    mainwindow.ui
    preferencewindow.ui
  )
    
  
    SET( KORSAIR_RCS
        rc.qrc
  )
  
  set(EXECUTABLE_OUTPUT_PATH ${korsair_SOURCE_DIR})
  
  # and finally an resource file
  
  # enable warnings
  ADD_DEFINITIONS( -Wall )
  
  # by default only QtCore and QtGui modules are enabled
  # other modules must be enabled like this:
  SET( QT_USE_QTWEBKIT TRUE )   
  
  # this command finds Qt4 libraries and sets all required variables
  # note that it's Qt4, not QT4 or qt4
  FIND_PACKAGE( Qt4 REQUIRED )
  
  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
  INCLUDE( ${QT_USE_FILE} )
  
  # this command will generate rules that will run rcc on all files from KORSAIR_RCS
  # in result KORSAIR_RC_SRCS variable will contain paths to files produced by rcc
  QT4_ADD_RESOURCES( KORSAIR_RC_SRCS ${KORSAIR_RCS} )
  
  # this will run uic on .ui files:
  QT4_WRAP_UI( KORSAIR_UI_HDRS ${KORSAIR_UIS} )
  
  # and finally this will run moc:
  QT4_WRAP_CPP( KORSAIR_MOC_SRCS ${KORSAIR_MOC_HDRS} )
  
  # we need this to be able to include headers produced by uic in our code
  # (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
  INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )
  
  # here we instruct CMake to build "kaudio" executable from all of the source files
  ADD_EXECUTABLE( korsair ${KORSAIR_SRCS} ${KORSAIR_MOC_SRCS} ${KORSAIR_RC_SRCS} ${KORSAIR_UI_HDRS} )
  
  # last thing we have to do is to tell CMake what libraries our executable needs,
  # luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
  TARGET_LINK_LIBRARIES( korsair ${QT_LIBRARIES} )
  
  install(
    TARGETS
        korsair
    RUNTIME DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin
)

