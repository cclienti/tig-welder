SOURCE_FILES	= $(wildcard */*.scad)
BUILD_PREFIX    = build
DEPS_FILES	= $(addprefix $(BUILD_PREFIX)/, $(patsubst %.scad, %.d, $(SOURCE_FILES)))
DXF_FILES	= $(addprefix $(BUILD_PREFIX)/, $(patsubst %.scad, %.dxf, $(SOURCE_FILES)))

SCAD_FLAGS      = --hardwarnings


all: $(DXF_FILES)

$(BUILD_PREFIX)/%.dxf: %.scad
	mkdir -p $(dir $@)
	openscad $(SCAD_FLAGS) -d $(patsubst %.dxf, %.d, $@) -o $@ $<

clean:
	rm -rf $(BUILD_PREFIX)

print-%:
	@echo $* = $($*)

-include $(DEPS_FILES)
