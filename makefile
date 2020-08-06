OBJDIR = targets/
CFLAGS = -Wall -Wextra -Werror -pedantic -g
OBJ = $(addprefix $(OBJDIR), $(patsubst %.c, %.o, $(wildcard *.c)))
CFILES = $(wildcard *.c)
TESTDIR = test_cases/checker/
TESTS = env exit

hsh: $(OBJDIR) $(OBJ)

	betty $(CFILES)
	@cc $(CFLAGS) -o hsh $(OBJ)
	cp hsh $(TESTDIR)

$(OBJDIR)%.o: %.c headersh.h
	cc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR);

.PHONY: clean
clean:
	@rm -rf $(OBJDIR)

.PHONY: test
test: hsh $(TESTDIR)tester.sh
	$(TESTDIR)tester.sh $(TESTS)


$(TESTDIR)tester.sh:
	echo "#!/bin/bash" >> $(TESTDIR)tester.sh
	echo "cd /mnt/c/Users/Holberton/Desktop/shell_v2/test_cases/checker;" >>$(TESTDIR)tester.sh
	echo "for TEST in \"<dollar>@\"" >>$(TESTDIR)tester.sh
	echo "do" >>$(TESTDIR)tester.sh
	echo "    if [ <dollar>TEST == "env" ];" >>$(TESTDIR)tester.sh
	echo "        then " >>$(TESTDIR)tester.sh
	echo "        ./env_test.sh" >>$(TESTDIR)tester.sh
	echo "    fi " >>$(TESTDIR)tester.sh
	echo "    if [ <dollar>TEST == "exit" ];" >>$(TESTDIR)tester.sh
	echo "        then" >>$(TESTDIR)tester.sh
	echo "        ./exit_test.sh" >>$(TESTDIR)tester.sh
	echo "        ./exit2_test.sh" >>$(TESTDIR)tester.sh
	echo "    fi" >>$(TESTDIR)tester.sh
	echo "    if [ <dollar>TEST == "shell" ];" >>$(TESTDIR)tester.sh
	echo "         then" >>$(TESTDIR)tester.sh
	echo "        ./simple_shell_test.sh" >>$(TESTDIR)tester.sh
	echo "        ./simple_shell2_test.sh" >>$(TESTDIR)tester.sh
	echo "        ./simple_shell3_test.sh" >>$(TESTDIR)tester.sh
	echo "    fi" >>$(TESTDIR)tester.sh
	echo "    if [ <dollar>TEST == "setenv" ];" >>$(TESTDIR)tester.sh
	echo "        then" >>$(TESTDIR)tester.sh
	echo "        ./set_unset_env_test.sh" >>$(TESTDIR)tester.sh
	echo "    fi" >>$(TESTDIR)tester.sh
	echo "    if [ <dollar>TEST == "unsetenv" ];" >>$(TESTDIR)tester.sh
	echo "        then" >>$(TESTDIR)tester.sh
	echo "        ./set_unset_env_test.sh" >>$(TESTDIR)tester.sh
	echo "    fi" >>$(TESTDIR)tester.sh
	echo "done" >>$(TESTDIR)tester.sh
	echo "cd - > /dev/null" >>$(TESTDIR)tester.sh
	echo "" >>$(TESTDIR)tester.sh
	chmod u+x $(TESTDIR)tester.sh