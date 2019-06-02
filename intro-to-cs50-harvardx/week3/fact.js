function fact (n) {
  if ( !Number.isInteger(n * 1) || n <= 0) throw new Error('n should be a positive integer')
  if (n > 1) return n * fact(n-1)
  else return 1
}

let arg = process.argv[2]
console.log(fact(arg))