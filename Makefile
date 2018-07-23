# Programe By Tu

OBJS := main.c win_ui.c bug_list.c
TARGET:= MiniBug
LINK := -lncursesw -lpthread


all:
	gcc  -o $(TARGET) $(OBJS) $(LINK)

clean:
	$(RM) -rf $(TARGET) *.o

install:
	cp $(TARGET) /usr/bin


