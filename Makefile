# Remote thermometer initial makefile
COMM_Module = arduino/comm/src
TERM_Module = arduino/term/src
CONTROL_Module = control/src
PRESENTATION_Module = presentation/src

CLEAN_ALL_MODULES = comm_clean t term_clean presentation_clean
ALL_MODULES = $(COMM_Module) $(TERM_Module) $(PRESENTATION_Module)

.PHONY: all
all: $(ALL_MODULES)

.PHONY: $(COMM_Module)
$(COMM_Module):
	@$(MAKE) -C $@;

.PHONY: $(TERM_Module)
$(TERM_Module):
	@$(MAKE) -C $@;

.PHONY: $(PRESENTATION_Module)
$(PRESENTATION_Module):
	@$(MAKE) -C $@;

.PHONY: clean
clean: $(CLEAN_ALL_MODULES)

.PHONY: comm_clean
comm_clean:
	@$(MAKE) clean -C $(COMM_Module);

.PHONY: term_clean
term_clean:
	@$(MAKE) clean -C $(TERM_Module);

.PHONY: presentation_clean 
presentation_clean:
	@$(MAKE) clean -C $(PRESENTATION_Module);


