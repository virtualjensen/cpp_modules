NAME	=	Identify

CXX = c++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address

SRCS	=	Base.cpp \
			main.cpp \

OBJS	=	$(SRCS:.cpp=.o)

$(NAME)	:	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all	: $(NAME)

clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all

