require "narray"
require "awesome_print"
require "./lagrange.rb"

module LagrangeCap
  def self.polynomial_generator(x_value, polynomial_size)
    (0..polynomial_size).inject(0) { |sum, power| sum + ((polynomial_size - power) * (x_value ** power)) }
  end
  
  def self.roots_of_unity(length, scaling = 1)
    (0..length).map do |i|
      Complex(scaling * Math.cos(2 * Math::PI * i / (length + 1)), scaling * Math.sin(2 * Math::PI * i / (length + 1)))
    end
  end
  
  def self.rmsd(data)
    Math.sqrt(data.each_with_index.inject(0) { |sum, (expected, index)| sum + ((data.length - index) - expected) ** 2 } / data.length)
  end
end

polynomial_size, failed = 10, false

while !failed
  data   = LagrangeCap.roots_of_unity(polynomial_size).map { |x| [x, LagrangeCap.polynomial_generator(x, polynomial_size)] }
  failed = Lagrange.new(*data).coefficients.map(&:abs).reverse.each_with_index.any? { |value, index| (value - index).abs > 0.25 }
  
  polynomial_size += 1
end

puts "Failed roots of unity with a polynomial of power #{polynomial_size}"

polynomial_size, failed = 10, false

while !failed
  data   = (0..polynomial_size).map { |x| [x, LagrangeCap.polynomial_generator(x, polynomial_size)] }
  failed = Lagrange.new(*data).coefficients.map(&:abs).reverse.each_with_index.any? { |value, index| (value - index).abs > 0.5 }
  
  polynomial_size += 1
end

puts "Failed integer values with a polynomial of power #{polynomial_size}"

polynomial_size, failed = 10, false

while !failed
  matrix_a = NMatrix[*LagrangeCap.roots_of_unity(polynomial_size).map { |x| (0..polynomial_size).map { |power| x ** power } }]
  vector_b = NVector[*LagrangeCap.roots_of_unity(polynomial_size).map { |x| LagrangeCap.polynomial_generator(x, polynomial_size) }]
  results  = (vector_b / matrix_a).to_a
  
  ap results
  
  failed   = results.map(&:abs).reverse.each_with_index.any? { |value, index| (value - index).abs > 0.5 }
  
  polynomial_size += 1
end

puts "Failed LU decomposition with a polynomial of power #{polynomial_size}"