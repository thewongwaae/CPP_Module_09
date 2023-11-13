NAME	= PMergeMe
CPP		= c++ -fsanitize=address
FLAGS	= -Wall -Wextra -Werror -std=c++98
RM		= rm -f

SRC		= main.cpp PMergeMe.cpp
INC		= PMergeMe.hpp

OBJ		= $(SRC:%.cpp=%.o)

all : $(NAME)

%.o : %.cpp $(INC)
	@printf "\033[0;32mGenerating objects... %-33.33s\r" "$@"
	@$(CPP) $(FLAGS) -c $< -o $@
	@printf "\033[0m"

$(NAME) : $(OBJ)
	@printf "\033[0;32mGenerating executable... %-33.33s\n" "$@"
	@$(CPP) $(FLAGS) $^ -o $@
	@printf "\033[0m"

clean :
	@printf "\033[0;31mCleaning objects... %-33.33s\n" "$(OBJ)"
	@$(RM) $(OBJ)
	@printf "\033[0m"

fclean : clean
	@printf "\033[0;31mCleaning executable... %-33.33s\n" "$(NAME)"
	@$(RM) $(NAME)
	@printf "\033[0m"

re : fclean all