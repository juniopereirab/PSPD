/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "contador.h"

bool_t
xdr_params(xdrs, objp)
	XDR *xdrs;
	params *objp;
{

	if (!xdr_array(xdrs, (char **)&objp->dados.dados_val, (u_int *)&objp->dados.dados_len, ~0, sizeof(char), (xdrproc_t)xdr_char))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->palavras.palavras_val, (u_int *)&objp->palavras.palavras_len, ~0, sizeof(char), (xdrproc_t)xdr_char))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_result(xdrs, objp)
	XDR *xdrs;
	result *objp;
{

	if (!xdr_int(xdrs, &objp->ocorrencias))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->cont))
		return (FALSE);
	return (TRUE);
}
