# DarkFlame Copyright (C) 2014 Alexey Shumeiko
#
# This file is part of DarkFlame.
#
# DarkFlame is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# DarkFlame is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with DarkFlame.  If not, see <http://www.gnu.org/licenses/>.
#
# For more details see LICENSE file.



##########
# Target #
##########

TARGET = host

#############
# Compilers #
#############

CC        = g++
LNK       = g++
OBJ_EXT   = o

LDFLAGS += -lglut -lGL -lGLU

##################
# Extended goals #
##################

DIST_GOALS         = dist $(filter dist-%,$(MAKECMDGOALS))
UTEST_GOALS        = utest $(filter utest-%,$(MAKECMDGOALS))
ATEST_GOALS        = atest $(filter atest-%,$(MAKECMDGOALS))

###############
# Directories #
###############

TMP_DIR            = /tmp

SRC_DIR            = src/cpp
AI_SRC_DIR         = src/cpp/ai
ENTITY_SRC_DIR     = src/cpp/entity
FUNCTION_SRC_DIR   = src/cpp/function
MATH_SRC_DIR       = src/cpp/math
MODEL_SRC_DIR      = src/cpp/model
PHYSIC_SRC_DIR     = src/cpp/physic
RENDERER_SRC_DIR   = src/cpp/renderer
WINDOW_SRC_DIR     = src/cpp/window
TEST_DIR           = test/cpp

BUILD_DIR          = $(TMP_DIR)/build
DIST_DIR           = $(TMP_DIR)/dist
TARGET_BUILD_DIR   = $(BUILD_DIR)/$(TARGET)
TARGET_DIST_DIR    = $(DIST_DIR)/$(TARGET)

UTEST_BUILD_DIR    = $(TARGET_BUILD_DIR)/utest
ATEST_BUILD_DIR    = $(TARGET_BUILD_DIR)/atest

VDIRS              = $(BUILD_DIR)\
                     $(DIST_DIR)\
                     $(TARGET_BUILD_DIR)\
                     $(TARGET_DIST_DIR)\
                     $(UTEST_BUILD_DIR)\
                     $(ATEST_BUILD_DIR)\
                     $(TARGET_BUILD_DIR)/ai\
                     $(TARGET_BUILD_DIR)/entity\
                     $(TARGET_BUILD_DIR)/function\
                     $(TARGET_BUILD_DIR)/math\
                     $(TARGET_BUILD_DIR)/model\
                     $(TARGET_BUILD_DIR)/physic\
                     $(TARGET_BUILD_DIR)/renderer\
                     $(TARGET_BUILD_DIR)/window

CFLAGS += -I$(SRC_DIR)\
          -I$(AI_SRC_DIR)\
          -I$(ENTITY_SRC_DIR)\
          -I$(FUNCTION_SRC_DIR)\
          -I$(MATH_SRC_DIR)\
          -I$(MODEL_SRC_DIR)\
          -I$(PHYSIC_SRC_DIR)\
          -I$(RENDERER_SRC_DIR)\
          -I$(WINDOW_SRC_DIR)\
          -fpermissive

###########################
# Source and object files #
###########################

SRC_OBJS        = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(SRC_DIR)/*.cpp))
AI_OBJS         = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(AI_SRC_DIR)/*.cpp))
ENTITY_OBJ      = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(ENTITY_SRC_DIR)/*.cpp))
FUNCTION_OBJS   = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(FUNCTION_SRC_DIR)/*.cpp))
MATH_OBJS       = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(MATH_SRC_DIR)/*.cpp))
MODEL_OBJS      = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(MODEL_SRC_DIR)/*.cpp))
PHYSIC_OBJS     = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(PHYSIC_SRC_DIR)/*.cpp))
RENDERER_OBJS   = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(RENDERER_SRC_DIR)/*.cpp))
WINDOW_OBJS     = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_BUILD_DIR)/%.$(OBJ_EXT),$(wildcard $(WINDOW_SRC_DIR)/*.cpp))

SRCS_OBJS       = $(SRC_OBJS)\
                  $(AI_OBJS)\
                  $(ENTITY_OBJS)\
                  $(FUNCTION_OBJS)\
                  $(MATH_OBJS)\
                  $(MODEL_OBJS)\
                  $(PHYSIC_OBJS)\
                  $(RENDERER_OBJS)\
                  $(WINDOW_OBJS)

UTEST_CPP       = $(patsubst $(TEST_DIR)/%,%,$(wildcard $(TEST_DIR)/unit*.cpp))
UTEST_CPP      += utils.cpp
UTEST_OBJS      = $(addprefix $(UTEST_BUILD_DIR)/,$(patsubst %.cpp,%.$(OBJ_EXT),$(UTEST_CPP)))

ATEST_CPP       = $(patsubst $(TEST_DIR)/%,%,$(wildcard $(TEST_DIR)/accept*.cpp))
ATEST_CPP      += utils.cpp
ATEST_OBJS      = $(addprefix $(ATEST_BUILD_DIR)/,$(patsubst %.cpp,%.$(OBJ_EXT),$(ATEST_CPP)))

###################
# Default targets #
###################

.PHONY: all clean rebuild $(DIST_GOALS)

all: $(DIST_GOALS)

rebuild: clean all

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)

$(VDIRS):
	mkdir $@

$(DIST_GOALS): $(VDIRS) $(SRCS_OBJS)

############################
# Compilation and building #
############################

$(SRCS_OBJS): $(TARGET_BUILD_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(UTEST_OBJS): $(UTEST_BUILD_DIR)/%.$(OBJ_EXT): $(TEST_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(UTEST_BUILD_DIR)/unit: $(UTEST_OBJS) $(SRCS_OBJS)
	$(LNK) $^ $(CFLAGS) $(LDFLAGS) -o $@

$(ATEST_OBJS): $(ATEST_BUILD_DIR)/%.$(OBJ_EXT): $(TEST_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(ATEST_BUILD_DIR)/accept: $(ATEST_OBJS) $(SRCS_OBJS)
	$(LNK) $^ $(CFLAGS) $(LDFLAGS) -o $@

################
# Unit testing #
################

.PHONY: $(UTEST_GOALS)

$(UTEST_GOALS): $(VDIRS) $(UTEST_BUILD_DIR)/unit
	$(UTEST_BUILD_DIR)/unit

##################
# Accept testing #
##################

.PHONY: $(UTEST_GOALS)

$(ATEST_GOALS): $(VDIRS) $(ATEST_BUILD_DIR)/accept
	$(ATEST_BUILD_DIR)/accept

######################
# Debug the Makefile #
######################

.PHONY: debug

debug:
	@echo test
