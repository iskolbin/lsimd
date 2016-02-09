local simd = require'simd'

local N = 1e6

local x = 10
local y = 20
local z = 30
local q = 40

local e = 30
local r = 60
local u = 80
local a = 35

local t = os.clock()
for i = 1, N do
	local a1 = x / e
	local a2 = y / r
	local a3 = z / u
	local a4 = q / a
end
print( 'Vanilla', os.clock() - t )

simd.v4set( 1, x, y, z, q )
simd.v4set( 2, e, r, u, a )

local v4div = simd.v4div
local t = os.clock()
for i = 1, N do
	v4div( 1, 2, 3 )
end

print( 'SIMD', os.clock() - t )
