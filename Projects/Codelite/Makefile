.PHONY: clean All

All:
	@echo "----------Building project:[ SDL_p2p - Debug ]----------"
	@cd "/home/luis/Code/iSSB/External/SDL/SDL_p2p/projects/codelite" && "$(MAKE)" -f  "SDL_p2p.mk"
	@echo "----------Building project:[ iSSB - Debug ]----------"
	@"$(MAKE)" -f  "iSSB.mk" && "$(MAKE)" -f  "iSSB.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ SDL_p2p - Debug ]----------"
	@cd "/home/luis/Code/iSSB/External/SDL/SDL_p2p/projects/codelite" && "$(MAKE)" -f  "SDL_p2p.mk"  clean
	@echo "----------Cleaning project:[ iSSB - Debug ]----------"
	@"$(MAKE)" -f  "iSSB.mk" clean
