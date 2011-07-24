#!/usr/bin/env ruby
i=0
f=nil
File.open(ARGV[0]).each { |line|
#	    puts "i=#{i}"
#		puts "line = #{line}"
#		puts "f = #{f.inspect}"
	    if line =~ /.*x.*/
			i=i+1
			f.close if i>1
			f = File.open("/tmp/M#{i}", 'w')
		else
			f.print line
		end
}
