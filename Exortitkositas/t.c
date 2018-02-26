#define MAX_TITKOS 4096
#define OLVASAS_BUFFER 512
#define KULCS_MERET 6
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

double
atlagos_szohossz (const char *titkos, int titkos_meret)
{
  int sz = 0;
  for (int i = 0; i < titkos_meret; ++i)
    if (titkos[i] == ' ')
      ++sz;

  return (double) titkos_meret / sz;
}

int
tiszta_lehet (const char *titkos, int titkos_meret)
{

  double szohossz = atlagos_szohossz (titkos, titkos_meret);

  return szohossz > 1.0 && szohossz < 20.0
    && strcasestr (titkos, "hogy") && strcasestr (titkos, "nem") 
    && strcasestr (titkos, "az") && strcasestr (titkos, "ha");

}

void
exor (const char kulcs[], int kulcs_meret, char titkos[], int titkos_meret)
{

  int kulcs_index = 0;

  for (int i = 0; i < titkos_meret; ++i)
    {

      titkos[i] = titkos[i] ^ kulcs[kulcs_index];
      kulcs_index = (kulcs_index + 1) % kulcs_meret;

    }

}

int
exor_tores (const char kulcs[], int kulcs_meret, char titkos[],
	    int titkos_meret)
{

  exor (kulcs, kulcs_meret, titkos, titkos_meret);

  return tiszta_lehet (titkos, titkos_meret);

}

int
main (void)
{
//ha csak kisbetuk vannak a kodban:
	int kulcs_abc[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
/*ha csak nagybetuk vannak a kodban:
int kulcs_abc[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};*/
/*ha kis- es nagybetuk vannak a kodban:
int kulcs_abc[]=
{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};*/
/*int kulcs_abc[]=
{'0','1','2','3','4','5','6','7','8','9'
,'-','*','+','/','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};*/
  char kulcs[KULCS_MERET];
  char titkos[MAX_TITKOS];
  char *p = titkos;
  int olvasott_bajtok;

  // titkos fajt berantasa
  while ((olvasott_bajtok =
	  read (0, (void *) p,
		(p - titkos + OLVASAS_BUFFER <
		 MAX_TITKOS) ? OLVASAS_BUFFER : titkos + MAX_TITKOS - p)))
    p += olvasott_bajtok;


  // maradek hely nullazasa a titkos bufferben  
  for (int i = 0; i < MAX_TITKOS - (p - titkos); ++i)
    titkos[p - titkos + i] = '\0';
  // osszes kulcs eloallitasa



  for (int ii = 0; ii < 24; ++ii)
    for (int ji = 0; ji < 24; ++ji)
      for (int ki = 0; ki < 24; ++ki)
	for (int li = 0; li < 24; ++li)
	  for (int mi = 0; mi < 24; ++mi)
	    for (int ni = 0; ni < 24; ++ni)
	   // for (int oi = '0'; oi <= '9'; ++oi)
	      //for (int pi = '0'; pi <= '9'; ++pi)
		  {
		    kulcs[0] = kulcs_abc[ii];
		    kulcs[1] = kulcs_abc[ji];
		    kulcs[2] = kulcs_abc[ki];
		    kulcs[3] = kulcs_abc[li];
		    kulcs[4] = kulcs_abc[mi];
		    kulcs[5] = kulcs_abc[ni];
		   // kulcs[6] = oi;
		   // kulcs[7] = pi;

		    if (exor_tores (kulcs, KULCS_MERET, titkos, p - titkos))
		      printf
			("Kulcs: [%c%c%c%c%c%c]\nTiszta szoveg: [%s]\n",
			 kulcs_abc[ii], kulcs_abc[ji], kulcs_abc[ki], kulcs_abc[li],kulcs_abc[mi], kulcs[ni], titkos);
  
		    exor (kulcs, KULCS_MERET, titkos, p - titkos);
		  }

  return 0;
}
