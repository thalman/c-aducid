#!/usr/bin/env perl


sub enum_java2c {
    $handle = shift;
    $type = shift;
    $enums = $type eq "enums";
    $prefix = shift;
    $fn = shift;
    if(defined $_[0]) { $class = shift; } else { undef $class; }
    open F, "< $fn";
    $work = 0;
    while( $line = <F> ) {
        chomp($line);
        if( $line =~ /public\s+enum\s+([-a-zA-Z0-9_]+)/ ) {
            if( ! defined $class ) {
                $class = $1;
            }
            if($enums) {
                print $handle "typedef enum {\n";
                print $handle "    ${prefix}INVALID = 0";
            } else {
                print $handle "const static char *${class}[] = {\n";
            }
            $work = 1;
        }
        if( $work ) {
            $found = 0;
            if( $line =~ /^\s*([-a-zA-Z0-9_]+)\("([-a-zA-Z0-9_]+)"\)/ ){
                $const = $1;
                $name = $2;
                $found = 1;
            }
            elsif( $line =~ /^\s*([-a-zA-Z0-9_]+)\s*[,;]/ ){
                $const = $1;
                $name = $const;
                $found = 1;
            }
            if( $found ) {
                if( $enums ) {
                    print $handle ",\n    $prefix$const";
                } else {
                    print $handle "    \"$name\",\n";
                }
            }
        }
        if( $line =~ /;/ ) { $work = 0; }
    }
    if( $enums ) {
        print $handle "\n} $class;\n\n";
    } else {
        print $handle "    NULL\n};\n\n";
    }
}


sub aducid_h(){
    open(I,"<aducid.h");
    open(O,">aducid.h.new");
    $suppress = 0;
    while( $line = <I> ) {
        if( $line =~ /ADUCID enum constants end/ ) { $suppress = 0; }
        if(! $suppress) { print O $line; }
        if( $line =~ /ADUCID enum constants begin/ ) {
            $suppress = 1;
            print O "\n";
            enum_java2c(O,"enums","ADUCID_OPERATION_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/OperationName.java","AducidOperation");
            enum_java2c(O,"enums", "ADUCID_ATTRIBUTE_SET_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AttributeSetName.java","AducidAttributeSet");
            enum_java2c(O,"enums", "ADUCID_AIM_STATUS_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AIMStatus.java","AducidAIMStatus");
            enum_java2c(O,"enums", "ADUCID_METHOD_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/MethodName.java","AducidMethod");
            enum_java2c(O,"enums", "ADUCID_ALGORITHM_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AlgorithmName.java","AducidAlgorithm");
            enum_java2c(O,"enums", "ADUCID_AUTHSTATUS_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AuthStatus.java","AducidAuthStatus");
            print O "\n";
        }
    }
}

sub aducid_c(){
    open(I,"<aducid.c");
    open(O,">aducid.c.new");
    $suppress = 0;
    while( $line = <I> ) {
        if( $line =~ /ADUCID text constants end/ ) { $suppress = 0; }
        if(! $suppress) { print O $line; }
        if( $line =~ /ADUCID text constants begin/ ) {
            $suppress = 1;
            print O "\n";
            enum_java2c(O,"names", "ADUCID_OPERATION_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/OperationName.java","aducidOperations");
            enum_java2c(O,"names", "ADUCID_ATTRIBUTE_SET_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AttributeSetName.java","aducidAttributeSets");
            enum_java2c(O,"names", "ADUCID_AIM_STATUS_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AIMStatus.java","aducidAIMStatuses");
            enum_java2c(O,"names", "ADUCID_METHOD_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/MethodName.java","aducidMethods");
            enum_java2c(O,"names", "ADUCID_ALGORITHM_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AlgorithmName.java","aducidAlgorithms");
            enum_java2c(O,"names", "ADUCID_AUTHSTATUS_","../../../../mod-api/src/main/java/com/aducid/sdk/enums/AuthStatus.java","aducidAuthStatuses");
            print O "\n";
        }
    }
}

aducid_h();
aducid_c();

rename "aducid.c", "aducid.c.bak";
rename "aducid.c.new", "aducid.c";

rename "aducid.h", "aducid.h.bak";
rename "aducid.h.new", "aducid.h";


