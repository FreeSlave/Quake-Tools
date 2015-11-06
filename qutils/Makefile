
BIN_DIR=bin
BUILD_DIR=build

LDFLAGS=-lm

INCLUDE_DIRS=-Icommon

QBSP_COMMON_SOURCES=common/bspfile.c common/cmdlib.c common/mathlib.c

QBSP_SOURCES=qbsp/brush.c  qbsp/map.c    qbsp/nodraw.c   qbsp/portals.c  qbsp/region.c    qbsp/surfaces.c  qbsp/writebsp.c qbsp/csg4.c   qbsp/merge.c  qbsp/outside.c  qbsp/qbsp.c     qbsp/solidbsp.c  qbsp/tjunc.c
QBSP_OBJECTS:=$(patsubst %.c,$(BUILD_DIR)/%.o,$(QBSP_SOURCES))
QBSP_COMMON_OBJECTS:=$(patsubst %.c,$(BUILD_DIR)/qbsp/%.o,$(QBSP_COMMON_SOURCES))
QBSP_DIRS=$(BUILD_DIR)/qbsp/common

VIS_COMMON_SOURCES=common/bspfile.c common/cmdlib.c common/mathlib.c

VIS_SOURCES=vis/flow.c  vis/soundpvs.c  vis/vis.c
VIS_OBJECTS:=$(patsubst %.c,$(BUILD_DIR)/%.o,$(VIS_SOURCES))
VIS_COMMON_OBJECTS:=$(patsubst %.c,$(BUILD_DIR)/vis/%.o,$(VIS_COMMON_SOURCES))
VIS_DIRS=$(BUILD_DIR)/vis/common

LIGHT_COMMON_SOURCES=common/bspfile.c common/cmdlib.c common/mathlib.c

LIGHT_SOURCES=light/entities.c  light/light.c  light/ltface.c  light/threads.c  light/trace.c
LIGHT_OBJECTS:=$(patsubst %.c,$(BUILD_DIR)/%.o,$(LIGHT_SOURCES))
LIGHT_COMMON_OBJECTS:=$(patsubst %.c,$(BUILD_DIR)/light/%.o,$(LIGHT_COMMON_SOURCES))
LIGHT_DIRS=$(BUILD_DIR)/light/common

all: qbsp vis light

qbsp: $(BIN_DIR) $(QBSP_DIRS) $(BIN_DIR)/qbsp
vis: $(BIN_DIR) $(VIS_DIRS) $(BIN_DIR)/vis
light: $(BIN_DIR) $(LIGHT_DIRS) $(BIN_DIR)/light

$(BIN_DIR):
	-mkdir -p $@

$(QBSP_DIRS):
	-mkdir -p $@
$(BIN_DIR)/qbsp: $(QBSP_OBJECTS) $(QBSP_COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $(QBSP_OBJECTS) $(QBSP_COMMON_OBJECTS) -o $@
$(BUILD_DIR)/qbsp/%.o: qbsp/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@
$(BUILD_DIR)/qbsp/common/%.o: common/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@


$(VIS_DIRS):
	-mkdir -p $@
$(BIN_DIR)/vis: $(VIS_OBJECTS) $(VIS_COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $(VIS_OBJECTS) $(VIS_COMMON_OBJECTS) -o $@
$(BUILD_DIR)/vis/%.o: vis/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@
$(BUILD_DIR)/vis/common/%.o: common/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@

$(LIGHT_DIRS):
	-mkdir -p $@
$(BIN_DIR)/light: $(LIGHT_OBJECTS) $(LIGHT_COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $(LIGHT_OBJECTS) $(LIGHT_COMMON_OBJECTS) -o $@
$(BUILD_DIR)/light/%.o: light/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@
$(BUILD_DIR)/light/common/%.o: common/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@
	
clean_qbsp:
	rm -rf $(BUILD_DIR)/qbsp $(BIN_DIR)/qbsp

clean_vis:
	rm -rf $(BUILD_DIR)/vis $(BIN_DIR)/vis

clean_light:
	rm -rf $(BUILD_DIR)/light $(BIN_DIR)/light

	
clean: clean_qbsp clean_vis clean_light

