big = []

Dir.glob("#{ENV['HOME']}/Documents/Mendeley Desktop/*.pdf") do |f|
  s = File.size(f)
  next if s < 100 * 1024 * 1024
  p f, s
  big.push(f)
end

require 'fileutils'

big.each do |f|
  FileUtils.cp f, "#{ENV['HOME']}/Documents/big"
end

p big.size
p big
