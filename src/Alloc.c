#include <ae2f/Ds/Alloc.h>
#include <stdlib.h>

ae2f_SHAREDEXPORT ae2f_extern ae2f_err_t ae2f_cDsAllocOwn_Init(
	ae2f_struct ae2f_cDsAllocOwn* This, 
	const ae2f_struct ae2f_vDsAlloc* imp
) {
	if (!(This)) return ae2f_errGlob_PTR_IS_NULL;
	if (!imp) return ae2f_ds_Alloc_Err_FPIMPNULL;

	This->data = 0;
	This->v = imp;

	return ae2f_errGlob_OK;
}

ae2f_SHAREDEXPORT ae2f_err_t ae2f_cDsAllocOwnCpy_imp(
	ae2f_struct ae2f_cDsAllocOwn* This, 
	const ae2f_struct ae2f_cDsAlloc* Another
) {
	if(!(This && Another)) 
	return ae2f_errGlob_PTR_IS_NULL;

	size_t size, elsize; ae2f_err_t err = ae2f_errGlob_OK;
	
	if ((err = ae2f_cDsAllocRefGetSize(Another, &size, &elsize)))
	return err;

	void* buff = calloc(size, elsize);
	if (!buff) return ae2f_errGlob_ALLOC_FAILED;
	
	if ((err = ae2f_cDsAllocRefGets(Another, 0, buff, size)))
		goto __GlobalFree;

	if ((err = ae2f_cDsAllocOwnReConfig(This, size, elsize)))
		goto __GlobalFree;

	if ((err = ae2f_cDsAllocOwnPuts(This, 0, buff, size * elsize)))
		goto __This_Architect_Failed;

	goto __GlobalFree;

	/// # Error occurred after `This`  
	__This_Architect_Failed:
	/// # Normal Error, from This not implemented.
	__GlobalFree:
	free(buff);
	return err;
}