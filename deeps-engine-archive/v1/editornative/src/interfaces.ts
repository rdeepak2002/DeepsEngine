export interface imageData {
    imageType: string;
    imageEncoding: string;
    imageData: string;
}

export interface playModeData {
    playMode: boolean;
}

export interface getEntitiesData {
    entities: Array<number>;
}

export interface messageData {
    name: string;
    data: object;
    status: string;
}

export interface Vec3 {
    x: number;
    y: number;
    z: number;
}

export interface Vec3Str {
    x: string | number;
    y: string | number;
    z: string | number;
}

export interface Transform {
    position: Vec3;
    rotation: Vec3;
    scale: Vec3;
}

export const genTransform = () => {
    return {
        position: {
            x: 0,
            y: 0,
            z: 0,
        },
        rotation: {
            x: 0,
            y: 0,
            z: 0,
        },
        scale: {
            x: 1,
            y: 1,
            z: 1,
        },
    };
}

export interface TransformStr {
    position: Vec3Str;
    rotation: Vec3Str;
    scale: Vec3Str;
}