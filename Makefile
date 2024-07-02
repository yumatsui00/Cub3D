CC = cc
CCFLAGS = -Wall -Wextra -Werror
MLXFLAG = -lmlx -framework OpenGL -framework
DEBUG = -g -fsanitize=address

SRCDIR = srcs
OBJDIR = objs
LIBFT = srcs/libft/libft.a

SRCS = srcs/k_cut_in_space.c
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)/%.o)

TARGET = Cub3D
TARGET1 = debug

all: $(TARGET)
	@make cub

debug: $(TARGET1)

$(TARGET): $(OBJS) $(LIBFT)
	# $(MAKE) -C srcs/libft
	$(CC) $(CCFLAGS) $(MLXFLAG) -o  $@ $^ $(LIBFT)
	@echo
	@echo $(YELLOW)$(BOLD)MAKE DONE

$(LIBFT):
	$(MAKE) -C srcs/libft

$(TARGET1): $(OBJS)
	@echo $(BRIGHT_YELLOW)
	# $(MAKE) -C srcs/libft
	$(CC) $(CCFLAGS) $(MLXFLAG) -o  $@ $^ $(LIBFT)
	@echo
	@echo FSANITIZE=ADDRESS DONE

$(OBJDIR):
	@echo $(GREEN)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/builtins
	@mkdir -p $(OBJDIR)/utils

$(OBJDIR)/%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	@make clean -C srcs/libft
	@rm -rf $(OBJDIR)
	@make printclean

fclean:
	@make fclean -C srcs/libft
	@rm -rf $(OBJDIR)
	@rm -f $(TARGET) $(TARGET1) $(TARGET2)
	@make printfclean

re:
	@make fclean
	@make all

.PHONY: all clean fclean re

# color
RESET = "\033[0m"
# 標準色
BLACK = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"
# 明るい色
BRIGHT_BLACK = "\033[90m"
BRIGHT_RED = "\033[91m"
BRIGHT_GREEN = "\033[92m"
BRIGHT_YELLOW = "\033[93m"
BRIGHT_BLUE = "\033[94m"
BRIGHT_MAGENTA = "\033[95m"
BRIGHT_CYAN = "\033[96m"
BRIGHT_WHITE = "\033[97m"
# 背景色
BG_RED = "\033[41m"
BG_GREEN = "\033[42m"
BG_BLUE = "\033[44m"
# テキスト属性
BOLD = "\033[1m"
UNDERLINE = "\033[4m"
REVERSE = "\033[7m"

cub:
	@echo $(BRIGHT_CYAN)$(BOLD)"┏━━━┓╋╋╋╋┏┓╋╋┏━━━┓┏━━━┓"
	@echo "┃┏━┓┃╋╋╋╋┃┃╋╋┃┏━┓┃┗┓┏┓┃"
	@echo "┃┃╋┗┛┏┓┏┓┃┗━┓┗┛┏┛┃╋┃┃┃┃"
	@echo "┃┃╋┏┓┃┃┃┃┃┏┓┃┏┓┗┓┃╋┃┃┃┃"
	@echo "┃┗━┛┃┃┗┛┃┃┗┛┃┃┗━┛┃┏┛┗┛┃"
	@echo "┗━━━┛┗━━┛┗━━┛┗━━━┛┗━━━┛"

printclean:
	@echo $(BRIGHT_MAGENTA)
	@echo ╭━╮╭╮╱╭━╮╭━━╮╭━┳╮╭━┳╮╭━━╮╭━┳╮╭━━╮
	@echo ┃╭╯┃┃╱┃┳╯┃╭╮┃┃┃┃┃┃┃┃┃╰┃┃╯┃┃┃┃┃╭━┫
	@echo ┃╰╮┃╰╮┃┻╮┃┣┫┃┃┃┃┃┃┃┃┃╭┃┃╮┃┃┃┃┃╰╮┃╭╮╭╮╭╮
	@echo ╰━╯╰━╯╰━╯╰╯╰╯╰┻━╯╰┻━╯╰━━╯╰┻━╯╰━━╯╰╯╰╯╰╯

printfclean:
	@echo $(RED)╭━━━╮$(BRIGHT_MAGENTA)
	@echo $(RED)┃╭━━╯$(BRIGHT_MAGENTA)
	@echo $(RED)┃╰━━╮$(BRIGHT_MAGENTA) ╭━╮╭╮╱╭━╮╭━━╮╭━┳╮╭━┳╮╭━━╮╭━┳╮╭━━╮
	@echo $(RED)┃╭━━╯$(BRIGHT_MAGENTA) ┃╭╯┃┃╱┃┳╯┃╭╮┃┃┃┃┃┃┃┃┃╰┃┃╯┃┃┃┃┃╭━┫
	@echo $(RED)┃┃ $(BRIGHT_MAGENTA) ╱╱┃╰╮┃╰╮┃┻╮┃┣┫┃┃┃┃┃┃┃┃┃╭┃┃╮┃┃┃┃┃╰╮┃╭╮╭╮╭╮
	@echo $(RED)╰╯ $(BRIGHT_MAGENTA)╱╱ ╰━╯╰━╯╰━╯╰╯╰╯╰┻━╯╰┻━╯╰━━╯╰┻━╯╰━━╯╰╯╰╯╰╯

coffee:
	@echo ""
	@echo "                   ("
	@echo "	                     )     ("
	@echo "               ___...(-------)-....___"
	@echo '           .-""       )    (          ""-.'
	@echo "      .-''''|-._             )         _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'