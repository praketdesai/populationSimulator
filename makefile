build: 
	@python3 script.py
	@g++ Allele.h Gene.h Dna.h Archetype.h Encounter.h People.h Environments.h test.cpp
	@./a.out
run:
	@python3 script.py
	@./a.out	
script:
	@python3 script.py
clean:
	@