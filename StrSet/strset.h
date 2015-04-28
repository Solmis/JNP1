#ifndef _STRSET_H
#define _STRSET_H

#include <stdio.h>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


/* Tworzy nowy zbiór i zwraca jego indentyfikator */
EXTERNC unsigned long strset_new();

/* Jeżeli istnieje zbiór o identyfikatorze id, usuwa go,
   a w przeciwnym wypadku nic nie robi */
EXTERNC void strset_delete(unsigned long id);


/* Jeżeli istnieje zbiór o identyfikatorze id, zwraca liczbę
   jego elementów, a w przeciwnym przypadku zwraca 0. */
EXTERNC size_t strset_size(unsigned long id);


/* Jeżeli istnieje zbiór o identyfikatorze id oraz element value jeszcze w nim
   nie istnieje, to go dodaje. W przeciwnym razie funkcja nie robi nic. */
EXTERNC void strset_insert(unsigned long id, const char* value);


/* Jeżeli istnieje zbiór o identyfikatorze id i element value w nim
   istnieje, to usuwa go, a w przeciwnym przypadku nie robi nic. */
EXTERNC void strset_remove(unsigned long id, const char* value);


/* Jeżeli istnieje zbiór o identyfikatorze id i element value w nim
   istnieje, to funkcja zwraca 1, w przeciwnym przypadku 0. */
EXTERNC int strset_test(unsigned long id, const char* value);


/* Jeżeli istnieje zbiór o identyfikatorze id, usuwa wszystkie
   jego elementy, a w przeciwnym przypadku nie robi nic. */
EXTERNC void strset_clear(unsigned long id);


/* Porównuje zbiory id1 i id2. Zwraca:
   -1, gdy id1 < id2
    0, gdy id1 = id2
    1, gdy id1 > id2   */
EXTERNC int strset_comp(unsigned long id1, unsigned long id2);


#undef EXTERNC
#endif