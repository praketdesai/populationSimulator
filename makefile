build: 
	@g++ Object.h Allele.h Gene.h Dna.h Archetype.h People.h People.cpp Environment.h test.cpp
	@./a.out
run:
	@python3 script.py
	@./a.out	
script:
	@python3 script.py
clean:
	@