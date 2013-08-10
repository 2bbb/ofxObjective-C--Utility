//
//  ofxObjective-C++Utility.h
//
//  Created by ISHII 2bit on 2013/08/08.
//
//

#ifndef __ofxObjective_C__Utility_h__
#define __ofxObjective_C__Utility_h__

#include "ofMain.h"

static NSString *convert(string str) {
    return [NSString stringWithCString:str.c_str()
                              encoding:NSUTF8StringEncoding];
}

static string convert(NSString* str) {
    return string([str cStringUsingEncoding:NSUTF8StringEncoding]);
}

static ofPoint convert(CGPoint &point) {
    return ofPoint(point.x, point.y);
}

static CGPoint convert(const ofPoint &p) {
    return (CGPoint) {
        .x = p.x,
        .y = p.y
    };
}

static ofRectangle convert(const CGRect &rect) {
    return ofRectangle(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

static CGRect convert(ofRectangle &r) {
    return (CGRect) {
        .origin.x = r.x,
        .origin.y = r.y,
        .size.width = r.width,
        .size.height = r.height
    };
}

static ofBuffer convert(NSData *data) {
    return ofBuffer((const char *)[data bytes], [data length]);
}

static void convert(ofBuffer &buffer, NSData *data) {
    buffer.set((const char *)[data bytes], [data length]);
}

static NSData *convert(const ofBuffer &buffer) {
    return [NSData dataWithBytes:buffer.getBinaryBuffer() length:buffer.size()];
}

template <class From, class To>
vector<To> convertToVectorFromNSArray(NSArray *array, To(^convertor)(From from)) {
    vector<To> vec;
    for(From from in array) {
        vec.push_back(convertor(from));
    }
    return vec;
}

template <class From, class To>
static NSArray *convertToNSArrayFromVector(vector<From> &vec, To(^convertor)(const From from)) {
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:vec.size()];
    for(int i = 0; i < vec.size(); i++) {
        [array addObject:convertor(vec[i])];
    }
    return [NSArray arrayWithArray:array];
}

static string(^convertFromNSStringToStringBlocks)(NSString *str) = ^string(NSString *str) {
    return convert(str);
};

static NSString *(^convertFromStringToNSStringBlocks)(string &str) = ^NSString *(string &str) {
    return convert(str);
};

#endif
