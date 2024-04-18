//Ana Stanciulescu 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void double_size_coll(int ****arr, int **rows, int **columns, int *bufsize)
{
	//we've run out of room; extend the buffer;
	int ***tmp, *aux_l, *aux_c;
	tmp = (int ***)realloc(*arr, 2 * *bufsize * sizeof(int **));
	aux_l = (int *)realloc(*rows, 2 * *bufsize * sizeof(int));
	aux_c = (int *)realloc(*columns, 2 * *bufsize * sizeof(int));
	if (tmp && aux_l && aux_c) {
		*arr = tmp;
		*rows = aux_l;
		*columns = aux_c;
		*bufsize = *bufsize * 2;
	} else {
		//could not extend the buffer; return failure code;
		printf("Eroare de alocare\n");
		exit(-1);
	}
}

void half_size_coll(int ****arr, int **rows, int **columns, int *bufsize)
{
	//too much allocated memory; half the buffer size needed;
	int ***tmp, *aux_l, *aux_c, size;
	size = *bufsize / 2;
	if (size == 0)
		size = 2;
	tmp = (int ***)realloc(*arr, size * sizeof(int **));
	aux_l = (int *)realloc(*rows, size * sizeof(int));
	aux_c = (int *)realloc(*columns, size * sizeof(int));
	if (tmp && aux_l && aux_c) {
		*arr = tmp;
		*rows = aux_l;
		*columns = aux_c;
		*bufsize = size;
	} else {
		//could not reduce the buffer; return failure code;
		printf("Eroare de alocare\n");
		exit(-1);
	}
}

void read_matrix(int ***a_ptr, int *linii, int *coloane)
{
	int n, m, i, j, **a;
	scanf("%d%d", &n, &m);
	*linii = n;
	*coloane = m;
	//create auxiliary matrix;
	a = (int **)malloc(n * sizeof(int *));
	if (!a) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (i = 0; i < n; i++) {
		a[i] = (int *)malloc(m * sizeof(int));
		if (!a[i]) {
			printf("Eroare la alocare\n");
			for (j = i - 1; j >= 0; j--)
				free(a[j]);
			free(a);
			exit(-1);
		}
		for (j = 0; j < m; j++)
			scanf("%d", &a[i][j]);
	}
	//add the matrix to the collection;
	*a_ptr = a;
}

void dimensions_matrix(int idx, int nr_mat, int ok, int *linii, int *coloane)
{
	//show the elements stored in the corresponding arrays;
	if (idx > nr_mat || idx < 0 || ok == 0)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", *linii, *coloane);
}

void print_matrix(int ***a_ptr, int idx, int nr_mat, int ok, int *linii,
				  int *coloane)
{
	int i, j;
	if (idx > nr_mat || idx < 0 || ok == 0) {
		printf("No matrix with the given index\n");
	} else {
		//show the entire matrix;
		for (i = 0; i < *linii; i++) {
			for (j = 0; j < *coloane; j++)
				printf("%d ", a_ptr[idx][i][j]);
			printf("\n");
		}
	}
}

void resize_matrix(int ***a_ptr, int idx, int nr_mat, int *linii,
				   int *coloane, int ok)
{
	int i, j, l, c, x, y;
	//create new arrays for the new line and column dimensions;
	int *new_l, *new_c;
	int **a;
	scanf("%d", &l);
	new_l = (int *)malloc(l * sizeof(int));
	if (!new_l) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (i = 0; i < l; i++)
		scanf("%d", &new_l[i]);
	scanf("%d", &c);
	new_c = (int *)malloc(c * sizeof(int));
	if (!new_c) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (i = 0; i < c; i++)
		scanf("%d", &new_c[i]);
	if (idx > nr_mat || idx < 0 || ok == 0) {
		printf("No matrix with the given index\n");
	} else {
		//create auxiliary matrix with elements from the original one;
		a = (int **)malloc(l * sizeof(int *));
		if (!a) {
			printf("Eroare la alocare\n");
			exit(-1);
		}
		for (i = 0; i < l; i++) {
			a[i] = (int *)malloc(c * sizeof(int));
			if (!a[i]) {
				printf("Eroare la alocare\n");
				for (j = i - 1; j >= 0; j--)
					free(a[j]);
				free(a);
				exit(-1);
			}
			x = new_l[i];
			for (j = 0; j < c; j++) {
				y = new_c[j];
				a[i][j] = a_ptr[idx][x][y];
			}
		}
		//free original matrix;
		for (i = 0; i < *linii; i++)
			free(a_ptr[idx][i]);
		free(a_ptr[idx]);
		//add the new matrix in collection;
		a_ptr[idx] = a;
		*linii = l;
		*coloane = c;
	}
	//free the arrays used for the new dimensions;
	free(new_l);
	free(new_c);
}

void matrix_prod_in_coll(int ****a_ptr, int idx1, int idx2, int **linii,
						 int **coloane, int *nr_mat, int *bufsize)
{
	int i, j, k, s, **a;
	if ((*coloane)[idx1] != (*linii)[idx2]) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		//create auxiliary matrix for the product;
		a = (int **)malloc((*linii)[idx1] * sizeof(int *));
		if (!a) {
			printf("Eroare la alocare\n");
			exit(-1);
		}
		for (i = 0; i < (*linii)[idx1]; i++) {
			a[i] = (int *)malloc((*coloane)[idx2] * sizeof(int));
			if (!a[i]) {
				for (j = i - 1; j >= 0; j--)
					free(a[j]);
				free(a);
				printf("Eroare la alocare\n");
				exit(-1);
			}
			for (k = 0; k < (*coloane)[idx2]; k++) {
				a[i][k] = 0;
				for (j = 0; j < (*coloane)[idx1]; j++) {
					s = ((*a_ptr)[idx1][i][j] * (*a_ptr)[idx2][j][k]) % 10007;
					if (s < 0)
						s = s + 10007;
					a[i][k] = (a[i][k] + s) % 10007;
					if (a[i][k] < 0)
						a[i][k] = a[i][k] + 10007;
				}
			}
		}
		//extend the number of matrixes and check for room;
		*nr_mat = *nr_mat + 1;
		if (*nr_mat == *bufsize)
			double_size_coll(a_ptr, linii, coloane, bufsize);
		//add the new matrix to the collection, on the last position;
		(*a_ptr)[*nr_mat] = a;
		(*linii)[*nr_mat] = (*linii)[idx1];
		(*coloane)[*nr_mat] = (*coloane)[idx2];
	}
}

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selection_sort(int **a, int nr_mat, int *linii, int *coloane)
{
	int i, j;
	for (i = 0; i <= nr_mat; i++) {
		int min_pos = i;
		for (j = i + 1; j <= nr_mat; j++)
			if (a[1][j] < a[1][min_pos])
				min_pos = j;
		if (min_pos != i) {
			swap(&a[1][min_pos], &a[1][i]);
			swap(&a[0][min_pos], &a[0][i]);
			swap(&linii[min_pos], &linii[i]);
			swap(&coloane[min_pos], &coloane[i]);
		}
	}
}

void org_matrix(int ****a_ptr, int nr_mat, int bufsize, int *linii,
				int *coloane)
{
	int i, j, s, **suma, ***colectie;
	int idx, nr;
	//create new collection that uses the new indexes;
	colectie = (int ***)malloc(bufsize * sizeof(int **));
	if (!colectie) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	//create new matrix for the indexes and matrix' sum;
	suma = (int **)malloc(2 * sizeof(int *));
	if (!suma) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (i = 0; i < 2; i++) {
		suma[i] = (int *)malloc(bufsize * sizeof(int));
		if (!suma[i]) {
			for (j = i - 1; j >= 0; j--)
				free(suma[j]);
			free(suma);
			printf("Eroare la alocare\n");
			exit(-1);
		}
	}
	//first line is only for indexes;
	for (idx = 0; idx <= nr_mat; idx++)
		suma[0][idx] = idx;
		//second line is for the actual sums;
	for (idx = 0; idx <= nr_mat; idx++) {
		s = 0;
		for (i = 0; i < linii[idx]; i++)
			for (j = 0; j < coloane[idx]; j++) {
				s = (s + a_ptr[0][idx][i][j]) % 10007;
				if (s < 0)
					s = s + 10007;
			}
		suma[1][idx] = s;
	}
	selection_sort(suma, nr_mat, linii, coloane);
	for (idx = 0; idx <= nr_mat; idx++) {
		nr = suma[0][idx];
		colectie[idx] = a_ptr[0][nr];
	}
	//free the initial collection and the matrix for sums;
	for (i = 0; i < 2; i++)
		free(suma[i]);
	free(suma);
	free(a_ptr[0]);
	//point to the new collection;
	*a_ptr = colectie;
}

void transp_matrix(int ***a_ptr, int nr_mat, int idx, int **linii,
				   int **coloane, int ok)
{
	int i, j, l, c, **a;
	if (idx > nr_mat || idx < 0 || ok == 0) {
		printf("No matrix with the given index\n");
	} else {
		//swap the number of lines with columns;
		l = (*coloane)[idx];
		c = (*linii)[idx];
		//create auxiliary matrix and transpose the original one;
		a = (int **)malloc(l * sizeof(int *));
		if (!a) {
			printf("Eroare la alocare\n");
			exit(-1);
		}
		for (i = 0; i < l; i++) {
			a[i] = (int *)malloc(c * sizeof(int));
			if (!a[i]) {
				for (j = i - 1; j >= 0; j--)
					free(a[j]);
				free(a);
				printf("Eroare la alocare\n");
				exit(-1);
			}
			for (j = 0; j < c; j++)
				a[i][j] = a_ptr[idx][j][i];
		}
		//free the original matrix;
		for (i = 0; i < (*linii)[idx]; i++)
			free(a_ptr[idx][i]);
		free(a_ptr[idx]);
		//point to the new matrix, as well as the new dimensions;
		a_ptr[idx] = a;
		(*linii)[idx] = l;
		(*coloane)[idx] = c;
	}
}

int **IN(int linii)
{
	int i, j, **a;
	//create the identity matrix;
	a = (int **)malloc(linii * sizeof(int *));
	if (!a) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (i = 0; i < linii; i++) {
		a[i] = (int *)malloc(linii * sizeof(int));
		if (!a[i]) {
			for (j = i - 1; j >= 0; j--)
				free(a[j]);
			free(a);
			printf("Eroare la alocare\n");
			exit(-1);
		}
		for (j = 0; j < linii; j++) {
			a[i][j] = 0;
			a[i][i] = 1;
		}
	}
	return a;
}

void matrix_prod(int **a, int **b, int linii, int ***aux)
{
	int i, j, k, s, **prod;
	//create auxiliary array for the product;
	prod = (int **)malloc(linii * sizeof(int *));
	if (!prod) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (i = 0; i < linii; i++) {
		prod[i] = (int *)malloc(linii * sizeof(int));
		if (!prod[i]) {
			for (j = i - 1; j >= 0; j--)
				free(prod[j]);
			free(prod);
			printf("Eroare la alocare\n");
			exit(-1);
		}
		for (k = 0; k < linii; k++) {
			prod[i][k] = 0;
			for (j = 0; j < linii; j++) {
				s = a[i][j] * b[j][k] % 10007;
				if (s < 0)
					s = s + 10007;
				prod[i][k] = (prod[i][k] + s) % 10007;
				if (prod[i][k] < 0)
					prod[i][k] = prod[i][k] + 10007;
			}
		}
	}
	//free the original matrix and point to the product matrix;
	for (i = 0; i < linii; i++)
		free((*aux)[i]);
	free(*aux);
	*aux = prod;
}

void exp_matrix(int ****a_ptr, int idx, int nr_mat, int *linii,
				int *coloane, int *putere, int ok)
{
	int **aux, i;
	if (idx > nr_mat || idx < 0 || ok == 0) {
		printf("No matrix with the given index\n");
	} else {
		if (*putere < 0) {
			printf("Power should be positive\n");
		} else {
			if (linii[idx] != coloane[idx]) {
				printf("Cannot perform matrix multiplication\n");
			} else {
				//auxiliary matrix is set as the identity matrix;
				aux = IN(linii[idx]);
				//exponentiating in a loop;
				while (*putere > 1) {
					if (*putere % 2 == 1)
						matrix_prod(aux, (*a_ptr)[idx], linii[idx], &aux);
					matrix_prod((*a_ptr)[idx], (*a_ptr)[idx], linii[idx],
								&(*a_ptr)[idx]);
					*putere = *putere / 2;
				}
				matrix_prod(aux, (*a_ptr)[idx], linii[idx], &(*a_ptr)[idx]);
				if (*putere == 0)
					matrix_prod(aux, aux, linii[idx], &(*a_ptr)[idx]);
				//free auxiliary matrix;
				for (i = 0; i < linii[idx]; i++)
					free(aux[i]);
				free(aux);
			}
		}
	}
}

void remove_matrix(int ****a_ptr, int idx, int *nr_mat, int *bufsize,
				   int **linii, int **coloane, int ok)
{
	int i, j;
	//free the memory for the required matrix;
	if (idx > *nr_mat || idx < 0 || ok == 0) {
		printf("No matrix with the given index\n");
	} else {
		for (j = 0; j < (*linii)[idx]; j++)
			free((*a_ptr)[idx][j]);
		free((*a_ptr)[idx]);
		for (i = idx; i < *nr_mat; i++) {
			(*a_ptr)[i] = (*a_ptr)[i + 1];
			(*linii)[i] = (*linii)[i + 1];
			(*coloane)[i] = (*coloane)[i + 1];
		}
		//reduce the number of matrixes and cut the size in half if needed;
		*nr_mat = *nr_mat - 1;
		if (*nr_mat == (*bufsize / 2 - 1))
			half_size_coll(a_ptr, linii, coloane, bufsize);
	}
}

void endgame(int ***a_ptr, int nr_mat, int *linii, int *coloane)
{
	int j;
	int i;
	//it's the end, so free all resources;
	for (i = 0; i <= nr_mat; i++) {
		for (j = 0; j < linii[i]; j++)
			free(a_ptr[i][j]);
		free(a_ptr[i]);
	}
	free(linii);
	free(coloane);
	free(a_ptr);
}

int main(void)
{
	int idx, idx1, idx2, nr_mat = -1, bufsize = 2;
	int ***colectie, *linii, *coloane, ok = 0, command, putere;
	char n;
	colectie = (int ***)malloc(bufsize * sizeof(int **));
	linii = (int *)malloc(bufsize * sizeof(int));
	coloane = (int *)malloc(bufsize * sizeof(int));
	if (!colectie || !linii || !coloane) {
		printf("Eroare de alocare\n");
		exit(-1);
	}
	//infinite loop to read the commands;
	while (1) {
		scanf("%c", &n); command = 0;
		if (n == 'L') {
			nr_mat++; ok = 1; command = 1;
			if (nr_mat == bufsize)
				double_size_coll(&colectie, &linii, &coloane, &bufsize);
			read_matrix(&colectie[nr_mat], &linii[nr_mat], &coloane[nr_mat]);
		}
		if (n == 'D') {
			scanf("%d", &idx); command = 1;
			dimensions_matrix(idx, nr_mat, ok, &linii[idx], &coloane[idx]);
		}
		if (n == 'P') {
			scanf("%d", &idx); command = 1;
			print_matrix(colectie, idx, nr_mat, ok, &linii[idx], &coloane[idx]);
		}
		if (n == 'C') {
			scanf("%d", &idx); command = 1;
			resize_matrix(colectie, idx, nr_mat, &linii[idx], &coloane[idx],
						  ok);
		}
		if (n == 'M') {
			scanf("%d%d", &idx1, &idx2); command = 1;
			if (idx1 < 0 || idx2 < 0 || idx1 > nr_mat || idx2 > nr_mat ||
			    ok == 0)
				printf("No matrix with the given index\n");
			else
				matrix_prod_in_coll(&colectie, idx1, idx2, &linii,
									&coloane, &nr_mat, &bufsize);
		}
		if (n == 'O') {
			command = 1;
			org_matrix(&colectie, nr_mat, bufsize, linii, coloane);
		}
		if (n == 'T') {
			scanf("%d", &idx); command = 1;
			transp_matrix(colectie, nr_mat, idx, &linii, &coloane, ok);
		}
		if (n == 'R') {
			scanf("%d%d", &idx, &putere); command = 1;
			exp_matrix(&colectie, idx, nr_mat, linii, coloane, &putere, ok);
		}
		if (n == 'F') {
			scanf("%d", &idx); command = 1;
			remove_matrix(&colectie, idx, &nr_mat, &bufsize, &linii, &coloane,
						  ok);
		}
		if (n == 'Q') {
			endgame(colectie, nr_mat, linii, coloane);
			bufsize = 2; command = 1;
			break;
		}
		if (command == 0)
			printf("Unrecognized command\n");
		scanf("\n");
	}
	return 0;
}
