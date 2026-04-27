#==================================================================================================
#
#  Makefile for the C++ Training
#
#  Copyright (C) 2015-2026 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Build rules
default:
	@echo "\nBuilding all tasks in chapter \"C++ Software Design\""
	@$(MAKE) --no-print-directory -C ./2_Cpp_Software_Design
	@echo "\nBuilding all tasks in chapter \"C++20 Concepts\""
	@$(MAKE) --no-print-directory -C ./3_Concepts
	@echo "\nBuilding all tasks in chapter \"C++20 Ranges\""
	@$(MAKE) --no-print-directory -C ./4_Ranges


# Cleanup
clean:
	@echo "Cleaning up..."
	@$(MAKE) --no-print-directory -C ./2_Cpp_Software_Design clean
	@$(MAKE) --no-print-directory -C ./3_Concepts clean
	@$(MAKE) --no-print-directory -C ./4_Ranges clean


# Setting the independent commands
.PHONY: default clean
