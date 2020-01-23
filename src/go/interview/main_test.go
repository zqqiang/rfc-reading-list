package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestIsUnique(t *testing.T) {
	assert.Equal(t, true, IsUnique("abc"), "Should work!")
	assert.Equal(t, false, IsUnique("abca"), "Should work!")
}
