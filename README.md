# CUPS Wrapper
Simple Go library for submitting documents for printing via CUPS.

## Install
 - Go Modules (recommended):
    - Add `require github.com/mad-penguins/cupsWrapper latest` to your `go.mod` file.
 - Manual installation
    - Run `go get -u github.com/mad-penguins/cupsWrapper` command
    
## Example

```go
package main

import (
   "fmt"
   "github.com/mad-penguins/cupsWrapper"
)

func main() {
   msg := cupsWrapper.CUPSSubmitDocument("/home/you/document.pdf", "MyDocumentDisplayName.pdf")
   if msg != "ok" {
      fmt.Println(msg)
   }
}

```
