#include "funciones.cpp"

/**
 * @brief 
 * 
 * @param pathArchivo 
 */
void descomprimir(string pathArchivo);

/**
 * @brief 
 * 
 * @param pathArchivo 
 */
void comprimir(string pathArchivo);

/**
 * @brief 
 * 
 * @param tabla 
 */
void inicializarTabla(HuffmanTable tabla[]);

/**
 * @brief 
 * 
 * @param pathArchivo 
 * @param tabla 
 */
void contarOcurrencias(string pathArchivo, HuffmanTable tabla[]);

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmpInfo(HuffmanTreeInfo a, HuffmanTreeInfo b);

/**
 * @brief 
 * 
 * @param lista 
 * @param tabla 
 */
void crearLista(List<HuffmanTreeInfo> &lista, HuffmanTable tabla[]);

/**
 * @brief 
 * 
 * @param lista 
 * @return HuffmanTreeInfo* 
 */
HuffmanTreeInfo *crearArbol(List<HuffmanTreeInfo> &lista);

/**
 * @brief 
 * 
 * @param raiz 
 * @param tabla 
 */
void cargarCodigosEnTabla(HuffmanTreeInfo *raiz, HuffmanTable tabla[]);

/**
 * @brief 
 * 
 * @param tabla 
 * @return Ocurrencias 
 */
Ocurrencias cantOcurrencias(HuffmanTable tabla[]);

/**
 * @brief 
 * 
 * @param path 
 * @return string 
 */
string nombreDelArchivo(string path);

/**
 * @brief 
 * 
 * @param pathArchivo 
 * @param extension 
 * @return FILE* 
 */
FILE *abrirArchivo(string pathArchivo, string extension);

/**
 * @brief 
 * 
 * @param pathArchivo 
 * @param tabla 
 */
void grabarArchivoComprimido(string pathArchivo, HuffmanTable tabla[]);

/**
 * @brief 
 * 
 * @param cod 
 * @param raiz 
 * @param c 
 * @return HuffmanTreeInfo* 
 */
HuffmanTreeInfo *crearRama(string cod, HuffmanTreeInfo *raiz, unsigned char c);

/**
 * @brief 
 * 
 * @param archivo 
 * @return HuffmanTreeInfo* 
 */
HuffmanTreeInfo *recomponerArbol(FILE *archivo);

/**
 * @brief 
 * 
 * @param raiz 
 * @param pathArchivo 
 * @param archivoComprimido 
 */
void reescribirArchivo(HuffmanTreeInfo *raiz, string pathArchivo, FILE *archivoComprimido);