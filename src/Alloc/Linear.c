#include <ae2f/Ds/Alloc.h>
#include <string.h>
#include <stdlib.h>

#define LEN_GETTER (*((size_t*)This->data))


static ae2f_err_t Len(const ae2f_struct ae2f_ds_cAlloc* This, size_t* buff, size_t* one) {
	ae2f_err_t err = ae2f_errGlob_OK; 
	size_t sz[1] = {0};

	if (!(This))
		return ae2f_errGlob_PTR_IS_NULL;

	size_t* p_sz = ((size_t*)This->data) ? ((size_t*)This->data) : sz;

	if(buff) *buff = *((size_t*)p_sz);
	else err |= ae2f_ds_Alloc_Err_NCOPIED;

	if(one) *one = 1;
	else err |= ae2f_ds_Alloc_Err_NCOPIED;
	return err;
}
static ae2f_err_t Read(const ae2f_struct ae2f_ds_cAlloc* This, size_t idx, void* buff, size_t bufflen) {
	if (!(This && This->data))
		return ae2f_errGlob_PTR_IS_NULL;

	if (idx + bufflen > LEN_GETTER)
		return ae2f_ds_Alloc_Err_IDX_INVALID;

	memcpy(buff, This->data + sizeof(size_t) + idx, bufflen);


	return ae2f_errGlob_OK;
}
static ae2f_err_t Write(ae2f_struct ae2f_ds_cAlloc* This, size_t idx, const void* buff, size_t bufflen) {
	if (!(This && This->data))
		return ae2f_errGlob_PTR_IS_NULL;

	if (idx + bufflen > LEN_GETTER)
		return ae2f_ds_Alloc_Err_IDX_INVALID;

	memcpy(This->data + sizeof(size_t) + idx, buff, bufflen);

	return ae2f_errGlob_OK;
}
static ae2f_err_t Make(ae2f_struct ae2f_ds_cAlloc* This, size_t l, size_t ellen) {
	if (!This)
		return ae2f_errGlob_PTR_IS_NULL;

	l *= ellen;

	void* _Try = This->data ? realloc(This->data, l + sizeof(size_t)) : calloc(l + sizeof(size_t), 1);

#define i ((size_t*)_Try)[0]
	if (_Try) {
		if (This->data) for (; i < l; i++)
			This->data[i] = 0;
	} else return ae2f_errGlob_ALLOC_FAILED;

	This->data = _Try;
	i = l;
#undef i
	return ae2f_errGlob_OK;
}
static ae2f_err_t Del(ae2f_struct ae2f_ds_cAlloc* This) {
	if (!This)
		return ae2f_errGlob_PTR_IS_NULL;

	if (This->data) {
		free(This->data);
		This->data = 0;
	}

	return ae2f_errGlob_OK;
}

ae2f_SHAREDEXPORT const struct ae2f_ds_vAlloc ae2f_ds_vAlloc_cLinear = 
{ 
	.GetSize = Len, 
	.Read = Read, 
	.Write = Write,

	.Del = Del,
	.ReConfig = Make
};