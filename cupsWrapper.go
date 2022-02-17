package cupsWrapper

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lcups
// #include "cupsDriver.h"
import "C"

func CUPSSubmitDocument(filePath string, fileName string) string {
	path := C.CString(filePath)
	name := C.CString(fileName)

	return C.GoString(C.submitDocument(path, name))
}
