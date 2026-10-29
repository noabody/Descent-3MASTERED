SET (HEADERS )
SET (CPPS )
IF(UNIX)
  SET (CPPS linux_lib.cpp)
ENDIF()

SET (SCRIPTS
  aigame2 AIGame3 aigame4 AIGame barney BatteriesIncluded
  BossCamera CanyonsCTF CellTestLevel ChrisTest clutter GameGauge
  generic Geodomes HalfPipe InfernalBolt Inversion LEVEL0 level10
  level11 Level12 level13 level14 LEVEL15 Level16 level17 level1
  level2 level3 level4 level5 Level6 level7 level8 Level9
  LevelS1 levelS2 Merc02 Merc1 Merc3 Merc4 merc5 Merc6
  Merc7 myPowerHouse Mysterious_Isle orbital Paranoia PiccuStation
  Polaris Quadsomniac RudeAwakening SewerRat testscript TrainingMission Y2K)

SET (SCRIPTTARGETS )

SET (GAME_SCRIPTS
  aigame2 AIGame3 aigame4 AIGame clutter generic testscript)

# --- Staging Setup ---
IF(UNIX AND NOT APPLE)
  # Stage static source assets into the build directory
  FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/scripts/data/linuxfullhog")
  FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data/linuxfullhog/"
       DESTINATION "${CMAKE_BINARY_DIR}/scripts/data/linuxfullhog"
       FILES_MATCHING REGEX "\\.([sS][tT][rR]|[oO][gG][fF]|[tT][xX][tT])$")
ENDIF()

IF(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET(WIN_SCRIPT_HOG_DIR "${CMAKE_BINARY_DIR}/scripts/win64hog")
  SET(WIN_SCRIPT_DEBUG_DIR "${CMAKE_BINARY_DIR}/scripts/debug")
  FILE(MAKE_DIRECTORY "${WIN_SCRIPT_HOG_DIR}" "${WIN_SCRIPT_DEBUG_DIR}")
  SET(WIN64_MODULE_STRING_NAMES
    Anarchy.str Anarchyi.str coop.str coopi.str CTF.str CTFi.str
    DMFC.str DMFCi.str entropy.str entropyi.str hoard.str hoardi.str
    Hyper.str hyperi.str lanclient.str lanclienti.str monster.str monsteri.str
    mtclient.str mtclienti.str tanarchy.str tanarchyi.str)
  SET(WIN64_MODULE_STRING_SOURCES)
  FOREACH(STRING_NAME ${WIN64_MODULE_STRING_NAMES})
    LIST(APPEND WIN64_MODULE_STRING_SOURCES
      "${CMAKE_CURRENT_SOURCE_DIR}/data/linuxfullhog/${STRING_NAME}")
  ENDFOREACH()
ENDIF()

# --- Build Script Targets ---
FOREACH(SCRIPT ${SCRIPTS})
  ADD_LIBRARY(${SCRIPT} SHARED ${CPPS} "${SCRIPT}.cpp")
  SET_TARGET_PROPERTIES(${SCRIPT} PROPERTIES PREFIX "")
  LIST(APPEND SCRIPTTARGETS ${SCRIPT})

  IF(WIN32)
    LIST(FIND GAME_SCRIPTS ${SCRIPT} GAME_SCRIPT_INDEX)
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
      IF(GAME_SCRIPT_INDEX EQUAL -1)
        TARGET_SOURCES(${SCRIPT} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/MS-LVL-X64.DEF")
      ELSE()
        TARGET_SOURCES(${SCRIPT} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/MS-GAME-X64.DEF")
      ENDIF()
      SET_TARGET_PROPERTIES(${SCRIPT} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${WIN_SCRIPT_HOG_DIR}"
        PDB_OUTPUT_DIRECTORY "${WIN_SCRIPT_DEBUG_DIR}"
        COMPILE_PDB_OUTPUT_DIRECTORY "${WIN_SCRIPT_DEBUG_DIR}"
        COMPILE_PDB_NAME "${SCRIPT}")
      TARGET_LINK_OPTIONS(${SCRIPT} PRIVATE /INCREMENTAL:NO)
    ELSE()
      IF(GAME_SCRIPT_INDEX EQUAL -1)
        TARGET_SOURCES(${SCRIPT} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/MS-LVL.DEF")
      ELSE()
        TARGET_SOURCES(${SCRIPT} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/MS-GAME.DEF")
      ENDIF()
    ENDIF()
  ENDIF()

  IF(UNIX AND NOT APPLE)
    # Direct output straight to the build tree staging area
    SET_TARGET_PROPERTIES(${SCRIPT} PROPERTIES
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/scripts/data/linuxfullhog")
  ENDIF()
ENDFOREACH()

# --- Windows HOG Target ---
IF(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
  ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_BINARY_DIR}/descent3mastered-win.hog"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${WIN64_MODULE_STRING_SOURCES} "${WIN_SCRIPT_HOG_DIR}"
    COMMAND $<TARGET_FILE:hogdir> "${CMAKE_BINARY_DIR}/descent3mastered-win.hog" "${WIN_SCRIPT_HOG_DIR}"
    DEPENDS hogdir ${SCRIPTTARGETS} ${WIN64_MODULE_STRING_SOURCES}
    COMMENT "Building the Win64 first-party script archive")
  ADD_CUSTOM_TARGET(descent3mastered_win_hog ALL
    DEPENDS "${CMAKE_BINARY_DIR}/descent3mastered-win.hog")
  INSTALL(FILES "${CMAKE_BINARY_DIR}/descent3mastered-win.hog" DESTINATION ${D3_GAMEDIR})
ENDIF()

# --- Linux HOG Target ---
IF(UNIX AND NOT APPLE)
  ADD_CUSTOM_TARGET(HogLinuxFull ALL
    COMMAND $<TARGET_FILE:HogMaker> "${CMAKE_BINARY_DIR}/descent3mastered-linux.hog" "${CMAKE_BINARY_DIR}/scripts/data/linuxfullhog/d3linuxfullhog.txt"
    DEPENDS ${SCRIPTTARGETS} HogMaker
    COMMENT "Generating native 64-bit d3-linux.hog..."
  )

  INSTALL(FILES "${CMAKE_BINARY_DIR}/descent3mastered-linux.hog" DESTINATION ${D3_GAMEDIR})
ENDIF()
