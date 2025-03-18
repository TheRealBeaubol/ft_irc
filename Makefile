
NAME		= 	ircserv

COLOR_1		= \033[1;38;5;28m
COLOR_2		= \033[1;38;5;120m
COLOR_3		= \033[1;38;5;240m
COLOR_4		= \033[1;38;5;255m
COLOR_5		= \033[1;38;5;248m
RESET		= \033[0m

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g -MMD -MP
IFLAGS		=	-I ./inc
RM			= 	@rm -rf
MK			=   mkdir -p

SRC_DIR		= 	src
BUILD_DIR   = 	.build
OBJ_DIR     = 	$(BUILD_DIR)/obj
DEP_DIR     = 	$(BUILD_DIR)/dep

SRC 		= 	main.cpp \
				error_draw.cpp \
				Client.cpp \
				ParseMessage.cpp
 
OBJS 		:= $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))
DEPS 		:= $(patsubst %.cpp,$(DEP_DIR)/%.d,$(SRC))

all: $(NAME)

$(NAME): $(OBJS)
			$(CXX) $(CXXFLAGS) $(IFLAGS) $(OBJS) -o $(NAME) 
			@printf "  ✅ $(COLOR_2)$(NAME) successfully compiled$(RESET)\n"
			@printf "  🔄 $(COLOR_3)$(NAME) is ready to run$(RESET) \n\n"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
			@mkdir -p $(@D)
			$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

clean:
			@printf "  👾 \033[1;4;38;5;240m$(NAME)$(RESET)   \n  $(COLOR_3)└──> 🗑️    $(COLOR_4).o and .d $(COLOR_5)have been deleted$(RESET)\n"
			$(RM) $(BUILD_DIR)

fclean: clean
			@printf "  $(COLOR_3)└──> 🗑️    $(COLOR_4)$(NAME) binary $(COLOR_5)has been deleted$(RESET)\n\n"	
			$(RM) $(NAME)

re:	fclean all

-include $(DEPS)

.PHONY:	re fclean all clean
