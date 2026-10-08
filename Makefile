NAME := webserv

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj

SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp" 2>/dev/null)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += -g3
debug: re

sanitize: CXXFLAGS += -g3 -fsanitize=address,undefined
sanitize: re

.PHONY: all clean fclean re debug sanitize
