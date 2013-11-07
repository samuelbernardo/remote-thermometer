# Remote thermometer initial makefile
COMM_Module = arduino/comm/src
TERM_Module = arduino/term/src
CONTROL_Module = control/src
PRESENTATION_Module = presentation/src

ALL_MODULES = $(COMM_Module) $(TERM_Module) $(PRESENTATION_Module)

.PHONY: all
all: $(ALL_MODULES)

.PHONY: comm
comm: 
	@$(MAKE) -C $(COMM_Module);

.PHONY: $(COMM_Module)
$(COMM_Module):
	@$(MAKE) -C $@;

.PHONY: $(TERM_Module)
$(TERM_Module):
	@$(MAKE) -C $@;

.PHONY: $(PRESENTATION_Module)
$(PRESENTATION_Module):
	@$(MAKE) -C $@;

