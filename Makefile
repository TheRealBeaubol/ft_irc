
NAME		= 	ircserv

COLOR_1		= \033[1;38;5;28m
COLOR_2		= \033[1;38;5;120m
COLOR_3		= \033[1;38;5;240m
COLOR_4		= \033[1;38;5;255m
COLOR_5		= \033[1;38;5;248m
RESET		= \033[0m

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g -MMD -MP
RM			= 	@rm -rf
MK			=   mkdir -p

SRC_DIR		= 	src/
BUILD_DIR   = 	.build
OBJ_DIR     = 	$(BUILD_DIR)/obj
DEP_DIR     = 	$(BUILD_DIR)/dep

SRC			=	main.cpp
OBJS        := $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)/%.o,$(SRC_DIR)$(SRC))
DEPS        := $(patsubst $(SRC_DIR)%.cpp,$(DEP_DIR)/%.d,$(SRC_DIR)$(SRC))

all: $(NAME)

$(NAME): $(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) 
			@printf "  ✅ $(COLOR_2)$(NAME) successfully compiled$(RESET)\n"
			@printf "  🔄 $(COLOR_3)$(NAME) is ready to run$(RESET) \n\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
			@mkdir -p $(@D)
			$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
			@printf "  👾 \033[1;4;38;5;240m$(NAME)$(RESET)   \n  $(COLOR_3)└──> 🗑️    $(COLOR_4).o and .d $(COLOR_5)have been deleted$(RESET)\n"
			$(RM) $(OBJS) $(DEPS) $(OBJ_DIR)

fclean: clean
			@printf "  $(COLOR_3)└──> 🗑️    $(COLOR_4)$(NAME) binary $(COLOR_5)has been deleted$(RESET)\n\n"	
			$(RM) $(NAME)

re:	fclean all

-include $(DEPS)

.PHONY:	re fclean all clean
